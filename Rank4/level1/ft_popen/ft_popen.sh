
NAME=$(basename "$1" .c)
cc -Wall -Wextra -Werror $1 main.c -o $NAME

echo "Testing $NAME..."
./$NAME

rm $NAME
