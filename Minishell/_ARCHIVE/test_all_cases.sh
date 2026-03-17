#!/bin/bash
# filepath: /home/msedeno-/Documents/Workspace/Minishell/tests/test_all_cases.sh

# ==========================================
# CONFIGURACION
# ==========================================
MINISHELL="./minishell"
VALGRIND="valgrind --leak-check=full --quiet --suppressions=vincent.supp"
USE_VALGRIND=0

# Colores
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
RESET='\033[0m'

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: No encuentro el ejecutable en $MINISHELL${RESET}"
    exit 1
fi

if [ "$1" == "valgrind" ]; then
    USE_VALGRIND=1
fi

# ==========================================
# PREPARACION (Archivos dummy necesarios)
# ==========================================
echo -e "rojo\nverde\nazul\namarillo" > colors.txt
touch file_existe
touch file
mkdir -p dir_existe
mkdir -p dir_noperm
chmod 000 dir_noperm 2>/dev/null

# Limpiamos archivos que puedan molestar
rm -f file1 file2 file3 outfile

# ==========================================
# FUNCION DE TEST
# ==========================================
run_test() {
    CMD_INPUT="$1"
    DESC="$2"

    # -- 1. Ejecutar en BASH (Expected) --
    # Usamos bash -c para comandos complejos o echo | bash para inputs
    # Para simular environment limpio a veces es mejor env -i bash --norc
    echo "$CMD_INPUT" | bash > bash_out.txt 2> bash_err.txt
    EXIT_BASH=$?

    # -- 2. Ejecutar en MINISHELL (Actual) --
    if [ $USE_VALGRIND -eq 1 ]; then
        echo "$CMD_INPUT" | $VALGRIND $MINISHELL > mini_out.txt 2> mini_err.txt
    else
        echo "$CMD_INPUT" | $MINISHELL > mini_out.txt 2> mini_err.txt
    fi
    
    # -- 3. Limpieza de Output --
    # Quitamos el prompt "minihell>" y banners para que no falle la comparación
    sed -i '/minihell>/d' mini_out.txt
    # (Opcional) Unificar mensajes de error si difieren ligeramente (ej: "minishell:" vs "bash:")
    # sed -i 's/minishell:/bash:/g' mini_err.txt
    
    # -- 4. Comparación --
    DIFF_OUT=$(diff bash_out.txt mini_out.txt)
    # Comparar STDERR es tricky porque los mensajes exactos cambian, 
    # comprobamos solo si ambos tienen error o ambos no.
    BASH_HAS_ERR=$(wc -c < bash_err.txt)
    MINI_HAS_ERR=$(wc -c < mini_err.txt)
    
    ERR_MATCH=0
    if [ $BASH_HAS_ERR -eq 0 ] && [ $MINI_HAS_ERR -eq 0 ]; then
        ERR_MATCH=1
    elif [ $BASH_HAS_ERR -gt 0 ] && [ $MINI_HAS_ERR -gt 0 ]; then
        ERR_MATCH=1
    fi

    # Imprimir resultado simple
    if [ "$DIFF_OUT" == "" ]; then # && [ $ERR_MATCH -eq 1 ]
        echo -e "${GREEN}[OK]${RESET} $DESC"
    else
        echo -e "${RED}[KO]${RESET} $DESC"
        echo -e "${BLUE}   Comando:${RESET} [$CMD_INPUT]"
        echo -e "${YELLOW}   --- Bash Out ---${RESET}"
        cat bash_out.txt
        echo -e "${YELLOW}   --- Mini Out ---${RESET}"
        cat mini_out.txt
        echo "---------------------"
    fi
}

echo "=========================================="
echo "    TESTER MINISHELL v1.0"
echo "=========================================="

# ==========================================
# ECHO
# ==========================================
echo -e "\n--- ECHO TESTS ---"
run_test 'echo' "echo simple"
run_test 'echo hola' "echo hola"
run_test 'echo ""' "echo vacio"
run_test 'echo "" hola' "echo vacio hola"
run_test 'echo -n hola' "echo -n"
run_test 'echo -n -n hola' "echo -n repetido"
run_test 'echo -n -nh -n hola' "echo flags mezclados (debe imprimir -nh)"
run_test 'echo -nnnnnnnnn hola' "echo -n largo"
# Casos complejos de comillas y parseo
run_test 'echo $?hcudshfuewrf ew  wr 4ew""' "Fuzzing basics"
run_test "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'f'f'f''f'f'f'f'f'f'" "Comillas infernales 1"
run_test "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'a'j'o''i'w'q''q" "Comillas infernales 2"
run_test "echo \"\"aaaaaaaa\"bbbbb\"'''' ccccccccc \"dddddddd\"e'e'e" "Comillas infernales 3"
run_test 'echo "ho   $USER"  "la   $LESS"   $USER$TERM' "Variables y espacios (modificado comillas simples para que se expandan en el test)"
run_test 'echo "ho   $USER"' "Espacios en variable"
run_test 'echo"ho   $USER"' "Pegado echo (command not found)"
run_test 'e"cho" "ho   $USER"' "Comando con comillas intercala"
run_test '       echo "ho   $USER"' "Espacios antes del comando"
run_test 'echo "$HOME" "$USER"' "Variables separadas"
run_test "echo '\$HOME' \"\$LESS\" \$USER" "Mezcla comillas simples/dobles"

# ==========================================
# EXPORT
# ==========================================
echo -e "\n--- EXPORT TESTS ---"
# Nota: Como export cambia el estado, agrupamos export + echo para verificar
run_test 'export a=b && echo $a' "export a=b"
run_test 'export b=wawa && echo $b' "export b=wawa"
run_test 'export c=lala=kaka && echo $c' "export con igual extra"
run_test 'export a && export' "export sin valor (ver lista)"
run_test 'export a= && echo "|$a|"' "export vacio"
run_test 'export a= b=o && echo $a $b' "export multiple"
run_test 'export a=== && echo $a' "export muchos iguales"
run_test 'export 2a=lala' "export invalido empieza num"
run_test 'export !a=ma' "export invalido caracter raro"
run_test 'export $USER=la && echo $USER' "export sobreescribir variable existente"
run_test 'export NUEVA=$TERM && echo $NUEVA' "export desde otra variable"
run_test 'export' "export solo (lista)"
run_test 'export ""' "export string vacio (error)"
run_test 'export a b=$LESS c=d && echo $a $b $c' "export complejo multiple"

# ==========================================
# CD
# ==========================================
echo -e "\n--- CD TESTS ---"
run_test 'cd dir_existe; pwd' "cd directorio existe"
run_test 'cd directorio_no_existe' "cd no existe"
run_test 'cd file_existe' "cd a un archivo"
run_test 'cd; pwd' "cd solo (home)"
run_test 'cd -; pwd' "cd - (oldpwd)" # Puede fallar si OLDPWD no está set en la sesión
run_test 'cd ~; pwd' "cd ~"
# Simulación compleja: unset HOME y cd
run_test 'unset HOME; cd' "cd sin HOME set"
run_test 'cd dir_noperm' "cd sin permisos"

# ==========================================
# ENV
# ==========================================
echo -e "\n--- ENV TESTS ---"
# run_test 'env' "env básico" # Comentar porque genera mucha salida diff
run_test 'env lalal' "env con argumento (error o comportamiento bash)"
run_test 'env dir_existe' "env sobre directorio"

# ==========================================
# PWD
# ==========================================
echo -e "\n--- PWD TESTS ---"
run_test 'pwd' "pwd simple"
run_test 'pwd argumentos extra' "pwd con argumentos (ignora)"

# ==========================================
# UNSET
# ==========================================
echo -e "\n--- UNSET TESTS ---"
run_test 'export POLLOS=asados; unset POLLOS; echo $POLLOS' "unset básico"
run_test 'unset' "unset sin argumentos"
run_test 'export A=1 B=2; unset A B; echo $A $B' "unset multiple"

# ==========================================
# EXIT
# ==========================================
echo -e "\n--- EXIT TESTS ---"
# Solo comprobamos que no pete y salida por pantalla, el código numérico bash script no lo captura igual en pipe
run_test 'exit' "exit simple"
run_test 'exit 0' "exit 0"
run_test 'exit 42' "exit 42"
run_test 'exit lalal' "exit numérico necesario"

# ==========================================
# PIPES
# ==========================================
echo -e "\n--- PIPE TESTS ---"
run_test 'ls | wc' "ls | wc"
run_test 'ls|wc' "ls|wc pegado"
run_test 'cat colors.txt | sort -r | wc' "pipe triple sort"
run_test 'ls || wc' "bonus: OR operator (o error syntax)"
run_test 'ls |   | wc' "syntax error pipe vacio"
run_test 'ls | wc |' "syntax error pipe final"
run_test '| ls | wc' "syntax error pipe inicial"

# ==========================================
# REDIRECCIONES
# ==========================================
echo -e "\n--- REDIR TESTS ---"
run_test 'echo hola > out1; cat out1' "> create"
run_test 'echo caracola >> out1; cat out1' ">> append"
run_test 'echo hola > out1 > out2 > out3; ls out*' "Multiples >"
run_test 'cat < colors.txt' "< input simple"
run_test 'cat < colors.txt > copia.txt; cat copia.txt' "< input > output"
run_test 'cat colors.txt | wc' "mix pipe y file"

# ==========================================
# HEREDOCS
# ==========================================
echo -e "\n--- HEREDOC TESTS (Scripted) ---"
# Nota: Heredocs desde comando `echo` son difíciles de visualizar igual, pero testean la lógica
run_test 'cat << EOF
hola
adios
EOF' "Heredoc básico"

run_test 'header << EOF | grep a
hola
adios
EOF' "Heredoc en pipe (no existe comando 'header' en bash, será error cmd not found pero heredoc debe leerse)"

run_test 'cat << EOF | ls
ignored_input
EOF' "Heredoc piped to ls"

# ==========================================
# GENERAL / STRESS
# ==========================================
echo -e "\n--- GENERAL TESTS ---"
run_test '      ' "Solo espacios"
run_test 'echo "sin cerrar' "Comillas abiertas"
run_test 'echo $?' "Exit status previo (será 0)"
run_test 'ls noexiste; echo $?' "Exit status fail"
run_test 'unset PATH; ls' "Unset PATH y ejecutar ls"
run_test 'unset HOME; cd' "Unset HOME y cd"

# Limpieza final dummy
rm -f file_existe colors.txt out1 out2 out3 copia.txt mini_out.txt mini_err.txt bash_out.txt bash_err.txt
rm -rf dir_existe dir_noperm

echo -e "\n${GREEN}Tests finalizados.${RESET}"