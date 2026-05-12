cat > texto.txt << EOF
holaa
holaa
EOF

NAME=$(basename "$1" .c)
cc -Wall -Wextra -Werror $1 -o $NAME

echo ">>Testing ./$NAME"
valgrind --leak-check=full --show-leak-kinds=all ./$NAME texto.txt | cat -e
rm texto.txt
rm $NAME
