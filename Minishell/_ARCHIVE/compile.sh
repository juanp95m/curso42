#!/bin/bash

# Colores
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RESET="\033[0m"

# 1. Función Normal (Solo make re)
just_make() {
	echo -e "${YELLOW}Ejecutando make${RESET}"
	make re
}
# 2. Función Make re & Run (Por defecto)
make_and_run() {
	echo -e "${GREEN}Ejecutando make re && ./minishell${RESET}"
	make re
	./minishell
}


# 3. Función Valgrind
run_valgrind() {
	echo -e "${GREEN}Ejecutando make re && valgrind con flags${RESET}"
	make re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell
}

# 4. Funcion Valgrind con Track children
run_valgrind_track_children() {
	echo -e "${GREEN}Ejecutando make re && valgrind con flags y track children${RESET}"
	make re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline.supp ./minishell
}

# Lógica de selección
if [ "$1" == "1" ]; then
	just_make
elif [ "$1" == "2" ]; then
	make_and_run
elif [ "$1" == "3" ]; then
	run_valgrind
elif [ "$1" == "4" ]; then
	run_valgrind_track_children
else
    echo "Selecciona el modo:"
    echo "1) Make re (Default)"
    echo "2) Make re & Run"
    echo "3) Valgrind (Leaks check)"
    echo "4) Valgrind (Leaks check) with Track Children"
    read -p "Opción [1]: " option
	option=${option:-1}
	
	case $option in
		1) just_make ;;
		2) make_and_run ;;
		3) run_valgrind ;;
		4) run_valgrind_track_children ;;
		*) echo "Opción inválida. Saliendo." ;;
	esac
fi
