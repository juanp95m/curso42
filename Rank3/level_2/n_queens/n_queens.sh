NAME=$(basename "$1" .c)

cc -Wall -Wextra -Werror "$1" -o $NAME
echo "Testing ./$NAME 4"
./$NAME 4 | cat -e
echo ""
echo "Testing ./$NAME 5"
./$NAME 5 | cat -e

echo ""
echo "Testing no arguments"
./$NAME

echo ""
echo "Testing 7"
./$NAME 7 | head -n 5 | cat -e

echo ""
echo "Testing no arguments"
./$NAME
echo "Testing 7"
./$NAME 7 | cat -e

rm $NAME