# Minishell - Guía de Trabajo en Equipo y Recursos

## 📋 División del Trabajo entre 2 Personas

### **Persona 1: Parsing y Gestión de Entrada**

#### Responsabilidades:

- **Lexer/Tokenizer** (20% del proyecto)
  
  - Dividir la línea de entrada en tokens
  - Identificar tipos de tokens (comandos, argumentos, operadores, redirecciones)
  - Manejo de comillas simples y dobles
  - Detección de errores de sintaxis básicos

- **Parser** (25% del proyecto)
  
  - Construir el árbol de sintaxis abstracta (AST)
  - Validar la sintaxis de los comandos
  - Gestionar la precedencia de operadores (pipes, redirecciones)
  - Crear estructuras de datos para los comandos

- **Expansión de Variables** (15% del proyecto)
  
  - Expandir variables de entorno ($VAR)
  - Implementar $? para el exit status
  - Manejo de expansión dentro de comillas dobles

### **Persona 2: Ejecución y Sistema**

#### Responsabilidades:

- **Ejecución de Comandos** (20% del proyecto)
  
  - Fork y execve
  - Búsqueda de ejecutables en PATH
  - Gestión de procesos hijos
  - Manejo de exit status

- **Redirecciones** (10% del proyecto)
  
  - Input redirection (<)
  - Output redirection (>, >>)
  - Here-doc (<<)
  - Gestión de file descriptors con dup2

- **Pipes** (10% del proyecto)
  
  - Crear pipes entre comandos
  - Conectar stdin/stdout entre procesos
  - Gestión de múltiples pipes en cadena

### **Responsabilidades Compartidas:**

#### Built-ins (Dividir entre ambos):

- **Persona 1**: `echo`, `export`, `unset`
- **Persona 2**: `cd`, `pwd`, `env`, `exit`

#### Infraestructura Común:

- **Signals** (5%): ctrl-C, ctrl-D, ctrl-\ - Decidir quién lo implementa
- **Historia y Prompt** (5%): readline, history - Decidir quién lo implementa
- **Main loop**: Colaborar juntos
- **Testing**: Ambos deben testear el trabajo del otro

---

## 📚 Recursos de Aprendizaje (de Fácil a Complejo)

### **Nivel 1: Fundamentos de Shell 🌱**

#### Conceptos Básicos:

1. **¿Qué es una Shell?**
   
   - [Writing Your Own Shell - Tutorial básico](https://brennan/2015/01/16/write-a-shell-in-c/)
   - Introducción clara y práctica para principiantes

2. **Comandos de Unix/Linux básicos**
   
   - `man bash` - Manual de bash (tu mejor amigo)
   - [Explain Shell](https://explainshell.com/) - Explica cualquier comando de shell

3. **Readline Library**
   
   - `man 3 readline` - Manual de la biblioteca
   - [GNU Readline Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

### **Nivel 2: Procesos y Sistema 🔧**

#### Gestión de Procesos:

1. **Fork y Exec**
   
   - `man fork`, `man execve`, `man wait`
   - [Fork Explained](https://www.geeksforgeeks.org/fork-system-call/) - GeeksforGeeks
   - Video: "Unix Processes in C" - CodeVault (YouTube)

2. **File Descriptors**
   
   - `man dup`, `man dup2`, `man pipe`
   - [File Descriptors Explained](https://www.bottomupcs.com/file_descriptors.xhtml)
   - Artículo: "Understanding File Descriptors"

3. **Signals**
   
   - `man signal`, `man sigaction`
   - [Linux Signals Tutorial](https://www.youtube.com/watch?v=5We_HtLlAbs) - Video explicativo

### **Nivel 3: Parsing y Lexing 📖**

#### Análisis Léxico y Sintáctico:

1. **Tokenization Básica**
   
   - [Building a Lexer](https://craftinginterpreters.com/scanning.html) - Crafting Interpreters
   - Conceptos aplicables a tu shell

2. **Abstract Syntax Tree (AST)**
   
   - [AST for Beginners](https://ruslanspivak.com/lsbasi-part7/) - Let's Build a Simple Interpreter
   - Cómo representar comandos en estructuras de datos

3. **Gramáticas y Parsing**
   
   - [Parsing Techniques](https://en.wikipedia.org/wiki/Parsing) - Wikipedia
   - Recursive Descent Parser - técnica recomendada para Minishell

### **Nivel 4: Características Avanzadas 🚀**

#### Implementación Específica:

1. **Pipes y Redirecciones**
   
   - [Implementing Pipes](https://www.rozmichelle.com/pipes-forks-dups/) - Tutorial detallado
   - `man 7 pipe` - Documentación completa

2. **Variables de Entorno**
   
   - `man getenv`, `man setenv`
   - [Environment Variables in C](https://www.tutorialspoint.com/c_standard_library/c_function_getenv.htm)

3. **Here-doc**
   
   - Estudiar comportamiento en bash: `cat << EOF`
   - Implementación con pipes temporales

### **Nivel 5: Testing y Debugging 🐛**

#### Herramientas Esenciales:

1. **Valgrind**
   
   - `valgrind --leak-check=full ./minishell`
   - [Valgrind Quick Start](http://www.valgrind.org/docs/manual/quick-start.html)

2. **GDB/LLDB**
   
   - Debugging de procesos fork
   - `set follow-fork-mode child/parent`

3. **Testers de la Comunidad**
   
   - [minishell_tester](https://github.com/LucasKuhn/minishell_tester)
   - [42_minishell_tester](https://github.com/zstenger93/42_minishell_tester)
   - Crear tus propios tests comparando con bash

### **Nivel 6: Recursos de Referencia 📚**

#### Documentación Crítica:

1. **Man Pages Esenciales**
   
   ```bash
   man bash          # Referencia principal
   man 2 fork        # System calls
   man 2 execve
   man 2 pipe
   man 2 dup2
   man 3 readline
   ```

2. **Libros Recomendados**
   
   - "Advanced Programming in the UNIX Environment" - Stevens
   - "The Linux Programming Interface" - Michael Kerrisk

3. **Repositorios de Referencia**
   
   - Buscar en GitHub: `42 minishell` (¡solo para entender conceptos, no copiar!)
   - [Bash Source Code](https://git.savannah.gnu.org/cgit/bash.git) - Para los valientes

---

## 🗓️ Timeline Sugerido (4-6 semanas)

### Semana 1-2: Fundamentos

- [ ] Setup del proyecto y Makefile
- [ ] Implementar prompt básico con readline
- [ ] Lexer/Tokenizer básico (Persona 1)
- [ ] Ejecución simple de comandos (Persona 2)

### Semana 3: Características Core

- [ ] Parser completo (Persona 1)
- [ ] Pipes (Persona 2)
- [ ] Built-ins básicos (Ambos)

### Semana 4: Redirecciones y Variables

- [ ] Expansión de variables (Persona 1)
- [ ] Redirecciones completas (Persona 2)
- [ ] Signals (Decidir quién)

### Semana 5: Refinamiento

- [ ] Testing exhaustivo
- [ ] Fix de bugs
- [ ] Memory leaks
- [ ] Edge cases

### Semana 6: Bonus (Opcional)

- [ ] && y || con paréntesis
- [ ] Wildcards (*)

---

## 💡 Tips de Colaboración

1. **Comunicación constante**: Usar Discord/Slack diariamente
2. **Git workflow**: Crear branches por feature, hacer PRs
3. **Code reviews**: Revisar el código del compañero antes de merge
4. **Pair programming**: Sesiones conjuntas para partes complejas
5. **Testing cruzado**: Cada uno testea el trabajo del otro
6. **Documentar**: Comentar código y decisiones de diseño
7. **Norminette**: Revisar juntos antes de cada commit

---

## ⚠️ Errores Comunes a Evitar

- ❌ No gestionar bien los file descriptors (leaks)
- ❌ Olvidar cerrar pipes no usados
- ❌ Race conditions con signals
- ❌ Memory leaks en el parsing
- ❌ No manejar comandos vacíos o solo espacios
- ❌ Olvidar el caso de comillas vacías `""` o `''`
- ❌ No testear con comandos largos o muchos pipes
- ❌ Usar funciones no autorizadas

---

## 🎯 Criterios de Éxito

- ✅ El shell ejecuta comandos simples correctamente
- ✅ Pipes funcionan con múltiples comandos
- ✅ Todas las redirecciones funcionan
- ✅ Variables de entorno se expanden correctamente
- ✅ Built-ins se comportan como en bash
- ✅ Signals manejados correctamente
- ✅ Sin memory leaks (excepto readline)
- ✅ Norminette passing
- ✅ Pasa todos los testers de la comunidad

---

**¡Buena suerte con Minishell! 🚀**
