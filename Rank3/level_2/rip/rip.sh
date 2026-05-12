NAME=$(basename "$1" .c)

cc -Wall -Wextra -Werror "$1" -o $NAME

echo "Testing ./$NAME '( ( )'"
./$NAME '( ( )' | cat -e

echo ""
echo "Testing ./$NAME '( ( ( ) ( ) ( ) ) ( ) )'"
./$NAME '( ( ( ) ( ) ( ) ) ( ) )' | cat -e

echo ""
echo "Testing empty string"
./$NAME "" | cat -e

echo ""
echo "Testing no args"
./$NAME

rm $NAME
