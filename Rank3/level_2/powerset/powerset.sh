NAME=$(basename "$1" .c)

cc -Wall -Wextra -Werror "$1" -o $NAME
echo "Testing ./$NAME 3 1 0 2 4 5 3"
./$NAME 3 1 0 2 4 5 3 | cat -e

echo ""
echo "Testing ./$NAME 12 5 2 1 8 4 3 7 11"
./$NAME 12 5 2 1 8 4 3 7 11 | cat -e

echo ""
echo "Testing no arguments"
./$NAME

echo ""
echo "Testing 0 1 -1"
./$NAME 0 1 -1 | cat -e

echo ""
echo "Testing 7 3 8 2"
./$NAME 7 3 8 2 | cat -e

rm $NAME

