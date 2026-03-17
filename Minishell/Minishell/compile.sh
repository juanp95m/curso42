#!/bin/bash

SUPFILE=minishell.supp
# Colores
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RESET="\033[0m"
BONUS=0
if [ "$1" == "bonus" ]; then
	BONUS=1
fi

just_make() {
	echo -e "${YELLOW}Executing make${RESET}"
	if [ "$BONUS" -eq 0 ]; then
		echo -e "${YELLOW}Compiling without bonus...${RESET}"
		make
	else
		echo -e "${YELLOW}Compiling with bonus...${RESET}"
		make bonus
	fi
}
make_and_run() {
    echo -e "${GREEN}Executing make re && ./minishell${RESET}"
    if [ "$BONUS" -eq 0 ]; then
        echo -e "${YELLOW}Compiling without bonus...${RESET}"
        make
    else
        echo -e "${YELLOW}Compiling with bonus...${RESET}"
        make bonus
    fi
    ./minishell
}

run_valgrind() {
    echo -e "${GREEN}Executing make re && valgrind without suppression${RESET}"
    if [ "$BONUS" -eq 0 ]; then
        echo -e "${YELLOW}Compiling without bonus...${RESET}"
        make
    else
        echo -e "${YELLOW}Compiling with bonus...${RESET}"
        make bonus
    fi
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
}

run_valgrind_supp() {
    echo -e "${GREEN}Executing make re && valgrind with flags${RESET}"
    if [ "$BONUS" -eq 0 ]; then
        echo -e "${YELLOW}Compiling without bonus...${RESET}"
        make
    else
        echo -e "${YELLOW}Compiling with bonus...${RESET}"
        make bonus
    fi
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$SUPFILE ./minishell
}

run_valgrind_supp_track_children() {
    echo -e "${GREEN}Executing make re && valgrind with flags and track children${RESET}"
    if [ "$BONUS" -eq 0 ]; then
        echo -e "${YELLOW}Compiling without bonus...${RESET}"
        make
    else
        echo -e "${YELLOW}Compiling with bonus...${RESET}"
        make bonus
    fi
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$SUPFILE --track-fds=yes --trace-children=yes ./minishell
}

echo "Selecciona el modo:"
echo "1) Make"
echo "2) Make & Run"
echo "3) Valgrind (Leaks check) Without Suppression"
echo "4) Valgrind (Leaks check) With Suppression"
echo "5) Valgrind (Leaks check) with Track Children"
read -p "Option: " option

case $option in
	1) just_make ;;
	2) make_and_run ;;
	3) run_valgrind ;;
	4) run_valgrind_supp ;;
	5) run_valgrind_supp_track_children ;;
	*) echo "Invalid option. Exiting." ;;
esac
