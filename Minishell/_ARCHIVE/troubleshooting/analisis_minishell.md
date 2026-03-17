# Análisis del Estado de Minishell

**Fecha de última revisión:** 10/02/2026

## 1. Resumen General

El proyecto ha avanzado significativamente hacia una arquitectura basada en **AST (Abstract Syntax Tree)**. Esto facilita enormemente la implementación de operadores lógicos (`&&`, `||`) y la jerarquía de ejecución.

- **Frontend (Lexer + Parser):** Muy avanzado. Genera un árbol de ejecución (`t_node`) en lugar de una lista plana.
- **Backend (Executor):** Implementado parcialmente. Ya recorre el árbol y ejecuta comandos, pipes y redirecciones básicas.
- **Señales:** Pendiente.
- **Expander:** Falta expansión de wildcards (`*`).

---

## 2. Estado por Módulos

### A. Frontend (Lexer & Parser) - ✅ 95% Completado
*   **Logros:**
    *   Lexer funcional con soporte para quotes y metacaracteres.
    *   Parser reconstruido para generar **AST** (`t_node`), soportando `NODE_PIPE`, `NODE_AND`, `NODE_OR`, `NODE_CMD`.
    *   Parsing de redirecciones (`<`, `>`, `>>`) y Heredoc (`<<`).
*   **Faltantes:**
    *   Validación exhaustiva de errores de sintaxis (ej. `|| command`, `command > > file`).

### B. Executor - ⚠️ 60% Completado
*   **Logros:**
    *   `src/executor.c` implementa recorrido de árbol (`traverse_tree`).
    *   Lógica `&&` y `||` implementada.
    *   `pipe()` implementado recursivamente.
    *   Redirecciones de archivos (`<`, `>`, `>>`) y `append` funcionando en `executor_utils.c`.
    *   Ejecución de Builtins vs Externos (`path` resolution).
*   **CRÍTICO / Faltantes:**
    *   **Heredoc (`<<`):** El parser detecta el delimitador, pero el executor **NO LO PROCESA**. Falta lógica para leer stdin hasta el delimitador y pasarlo al comando (vía pipe o archivo temporal).
    *   **Control de Exit Codes:** `shell->last_exit_code` se actualiza, pero asegurar que `waitpid` recupere el código correcto en todos los casos de pipelines y subshells.

### C. Signals (Señales) - ❌ 5% Completado
*   **Estado:** `src/signals.c` está vacío (solo comentarios TODO).
*   **Requerido:**
    *   **Modo Interactivo:** `CTRL+C` (nueva línea), `CTRL+\` (ignorar), `CTRL+D` (exit - semi implementado en main).
    *   **Modo Ejecución (Blocking):** `CTRL+C` debe matar al proceso hijo y no a la shell. `CTRL+\` debe hacer Core Dump del hijo.
    *   **Heredoc:** `CTRL+C` debe cancelar el heredoc y volver al prompt.

### D. Expander - ⚠️ 50% Completado
*   **Logros:**
    *   Expansión de variables (`$VAR`) y exit code (`$?`).
    *   Quotations removal.
*   **Faltantes:**
    *   **Wildcards (`*`):** No hay lógica para expandir `*.c` a lista de archivos. Es obligatorio en la mayoría de versiones de Minishell.

### E. Builtins - ✅ 85% Completado
*   **Estado:** Implementados en `src/builtins/`.
*   **Detalle:** `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset` parecen funcionales y conectados.

---

## 3. Plan de Acción Inmediato (Prioridad)

1.  **Implementar Signals (`src/signals.c`):**
    *   Es vital para una shell funcional. Configurar `sigaction` para interactivo y ejecución.
2.  **Implementar Heredoc (`<<`):**
    *   Crear función en executor que, antes de ejecutar el comando, lea input hasta el delimitador.
3.  **Implementar Wildcards (`*`):**
    *   Integrar con `readdir` o `glob` en la fase de expansión.
4.  **Pruebas de Estrés:**
    *   Probar pipelines largos y combinaciones lógicas complejas `ls | grep a && echo yes || echo no`.

---
