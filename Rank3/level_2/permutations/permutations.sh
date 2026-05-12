NAME=$(basename "$1" .c)

cc -Wall -Wextra -Werror "$1" -o $NAME
echo "Testing ./$NAME a"
./$NAME a | cat -e

echo ""
echo "Testing ./$NAME ab"
./$NAME ab | cat -e

echo ""
echo "Testing ./$NAME abc"
./$NAME abc | cat -e

echo ""
echo "Testing no args"
./$NAME
rm $NAME
