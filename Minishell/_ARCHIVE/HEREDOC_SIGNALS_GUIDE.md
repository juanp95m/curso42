# Gestión de Heredoc y Señales en Minishell

## 🎯 Análisis de tu Código Actual

Tu implementación actual en [`signals_heredoc.c`](src/signals_heredoc.c) **YA ES CORRECTA** para la norma de 42:

### ✅ Lo que tienes bien:

1. **Una sola variable global**: `g_signal_status` (línea 13 en [`main.c`](src/main.c))
2. **Fork para heredoc**: El hijo maneja el readline, el padre hace cleanup
3. **Handler simple**: Solo modifica `g_signal_status` y hace `exit(130)`
4. **Limpieza en el padre**: Detecta exit status 130 y elimina el archivo

---

## 📝 Cambios Conceptuales Necesarios

Según tu arquitectura actual, aquí está cómo debe fluir:

### **1. Momento de Procesamiento: Durante el PARSING**

Revisando tu código, veo que procesas heredocs en [`parser_redirections.c`](src/parser_redirections.c). Necesitas asegurarte de que:

```c
// filepath: /home/jperez-m/Minishell/Minishell/src/parser_redirections.c
// ...existing code...

/**
 * @brief Parse heredoc redirection
 * @param command The command structure to update
 * @param tokens Pointer to current token position
 * @param shell Pointer to shell for heredoc_count
 * @return 1 on success, 0 on failure or Ctrl+C
 */
int	parse_heredoc(t_command *command, t_token **tokens, t_shell *shell)
{
	char	*delimiter;
	int		fd;

	if (!*tokens || (*tokens)->type != HEREDOC)
		return (0);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near heredoc\n", 2);
		return (0);
	}
	delimiter = (*tokens)->value;
	
	// Procesar heredoc (hace fork internamente)
	fd = process_heredoc(delimiter, shell->heredoc_count++);
	
	// Si Ctrl+C (retorna -1 y g_signal_status = 130)
	if (fd == -1)
		return (0); // Esto abortará el parsing
	
	// Guardar el fd en el comando
	command->infile = fd;
	*tokens = (*tokens)->next;
	return (1);
}

// ...existing code...
```

---

### **2. Propagar `shell` a través del Parser**

Necesitas modificar las firmas de las funciones de parsing para recibir `shell`:

```c
// filepath: /home/jperez-m/Minishell/Minishell/includes/minishell.h
// ...existing code...

// src/parser.c
t_node	*parser(t_token *tokens, t_shell *shell);
t_node	*parse_expression(t_token **tokens, t_shell *shell);
t_node	*parse_pipe(t_token **tokens, t_shell *shell);
t_node	*parse_simple_cmd(t_token **tokens, t_shell *shell);

// src/parser_redirections.c
int	dispatch_redirections(t_command *cmd, t_token **tokens, t_shell *shell);
int	parse_infile(t_command *command, t_token **tokens, t_shell *shell);
int	parse_outfile(t_command *command, t_token **tokens, t_shell *shell);
int	parse_heredoc(t_command *command, t_token **tokens, t_shell *shell);
int	parse_append(t_command *command, t_token **tokens, t_shell *shell);

// ...existing code...
```

---

### **3. Actualizar [`main_loop.c`](src/main_loop.c)**

```c
// filepath: /home/jperez-m/Minishell/Minishell/src/main_loop.c
// ...existing code...

void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_node	*ast;

	if (!input || input[0] == '\0')
		return ;
	add_history(input);
	tokens = lexer(input);
	if (!tokens)
		return ;
	shell->current_tokens = tokens;
	
	// Parser ahora recibe shell para heredoc_count
	ast = parser(tokens, shell);
	
	// Si Ctrl+C durante heredoc, ast será NULL
	if (!ast)
	{
		// Verificar si fue por Ctrl+C
		if (g_signal_status == 130)
		{
			shell->last_exit_code = 130;
			g_signal_status = 0;
		}
		free_tokens(tokens);
		shell->current_tokens = NULL;
		return ; // Volver al prompt sin ejecutar
	}
	
	shell->current_ast = ast;
	shell->last_exit_code = executor(ast, shell);
	free_ast(ast);
	free_tokens(tokens);
	shell->current_tokens = NULL;
	shell->current_ast = NULL;
}

// ...existing code...
```

---

### **4. Mantener tu implementación actual de `process_heredoc`**

Tu código actual en [`signals_heredoc.c`](src/signals_heredoc.c) **NO NECESITA CAMBIOS**:

```c
// filepath: /home/jperez-m/Minishell/Minishell/src/signals_heredoc.c
// ...existing code...

/**
 * @brief Process a heredoc by reading lines until the delimiter is encountered.
 * Uses fork to handle Ctrl+C properly and allow parent to cleanup.
 */
int	process_heredoc(char *delimiter, int heredoc_num)
{
	char	*filename;
	pid_t	pid;
	int		status;
	int		tmp_fd;

	filename = generate_heredoc_name(heredoc_num);
	if (!filename)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (free(filename), -1);
	if (pid == 0)
		heredoc_child_process(filename, delimiter);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		unlink(filename);          // Elimina archivo temporal
		free(filename);            // Libera memoria del nombre
		g_signal_status = 130;     // Indica Ctrl+C al padre
		return (-1);               // Señal de error
	}
	tmp_fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	return (tmp_fd);
}

// ...existing code...
```

---

## 📋 Resumen de Cambios Necesarios

### **Archivos a modificar:**

1. **[`parser.c`](src/parser.c)**: Añadir parámetro `t_shell *shell` a todas las funciones
2. **[`parser_redirections.c`](src/parser_redirections.c)**: Añadir parámetro `t_shell *shell` a `parse_heredoc` y otras funciones de redirección
3. **[`main_loop.c`](src/main_loop.c)**: Llamar a `parser(tokens, shell)` y manejar el retorno NULL cuando `g_signal_status == 130`
4. **[`minishell.h`](includes/minishell.h)**: Actualizar prototipos de funciones

### **Archivos que NO necesitas modificar:**

- ✅ [`signals_heredoc.c`](src/signals_heredoc.c) - Ya está correcto
- ✅ [`signals.c`](src/signals.c) - Ya está correcto
- ✅ [`main.c`](src/main.c) - La global `g_signal_status` ya existe

---

## 🎯 Flujo Completo

```
Input: cat << EOF | grep hello
       ↓
    LEXER (ya funciona)
       ↓
    PARSER (añadir shell*)
       ↓
    parse_heredoc() encuentra <<
       ↓
    process_heredoc() - fork()
       ↓
    HIJO: readline hasta EOF
          Si Ctrl+C → exit(130)
       ↓
    PADRE: waitpid detecta 130
           unlink(filename)
           free(filename)
           g_signal_status = 130
           return -1
       ↓
    parse_heredoc() retorna 0
       ↓
    parser() retorna NULL
       ↓
    process_input() detecta NULL + g_signal_status==130
           No ejecuta, vuelve al prompt
```

---

## 🎯 Concepto: Gestión de Heredoc con AST

### **Momento de Procesamiento**

En tu arquitectura actual:

```
Input → Lexer → Parser (construye AST) → Executor (recorre AST)
```

**El heredoc debe procesarse durante el PARSING, NO durante la ejecución.**

### **¿Por qué?**

1. **Lectura interactiva**: El heredoc requiere interacción con el usuario (`readline("> ")`)
2. **Señales tempranas**: Si presionas Ctrl+C durante el heredoc, debe **abortar todo el parsing**, no solo ese comando
3. **Archivo temporal**: El heredoc crea un archivo que se referencia en el AST como un descriptor de archivo

### **Flujo Correcto**

```
Usuario escribe: cat << EOF | grep hello
                    ↓
              ┌─────────┐
              │  LEXER  │
              └─────────┘
                    ↓
         [cat] [<<] [EOF] [|] [grep] [hello]
                    ↓
              ┌─────────┐
              │ PARSER  │ ← Aquí se procesa el heredoc
              └─────────┘
                    ↓
    Al encontrar <<: llama process_heredoc()
         - Fork child
         - Child: readline hasta delimitador
         - Si Ctrl+C: child exit(130)
         - Parent detecta: aborta parsing completo
         - Parent guarda fd en el nodo AST
                    ↓
              ┌─────────┐
              │   AST   │
              └─────────┘
                 PIPE
                /    \
              CMD    CMD
             (cat)  (grep)
           infile=fd  
                    ↓
              ┌─────────┐
              │EXECUTOR │ ← Solo lee del fd ya creado
              └─────────┘
```

---

## ✅ Resumen Conceptual

1. **Heredoc = Fase de Parsing**: No es parte de la ejecución
2. **Fork obligatorio**: Para manejar Ctrl+C limpiamente
3. **Propagación de `shell`**: Todas las funciones de parsing necesitan acceso
4. **Retorno -1**: Indica fallo (Ctrl+C), parser aborta completamente
5. **Una sola global**: `g_signal_status` para indicar la señal
6. **Archivo temporal**: Eliminado por el padre si child exit(130)

---

## 🔑 Restricción de la Norma de 42

> **Usa como máximo una variable global para indicar la recepción de una señal.**
> 
> Piensa en lo que implica: Esta aproximación evita que tu gestor de señales acceda
> a tus estructuras de datos principales.
> 
> ¡Cuidado! Esta variable global no puede proporcionar ninguna información o dato 
> más allá del número de la señal recibida. Por lo tanto, está prohibido utilizar 
> estructuras de tipo "norm" como variables globales.

### **Solución implementada:**

- ✅ **Una sola global**: `int g_signal_status`
- ✅ **Handler no accede a estructuras**: Solo modifica `g_signal_status` y hace `exit(130)`
- ✅ **Limpieza en proceso padre**: El padre detecta el exit status y hace cleanup
- ✅ **Sin race conditions**: Fork + waitpid garantiza la sincronización
