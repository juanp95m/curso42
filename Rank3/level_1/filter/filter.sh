
NAME=$(basename "$1" .c)
cc -Wall -Wextra -Werror $1 -o $NAME

TEST="xyzabcxyzacbzyxabc"
REP="abc"

echo "$>echo $TEST | ./$NAME $REP"
echo $TEST | ./$NAME $REP | cat -e

echo ""
echo "$>echo $TEST | ./$NAME $REP"
echo $TEST | ./$NAME $REP <&-


TEST=""
REP=""

echo ""
echo "testing empty string"
echo "$>echo $TEST | ./$NAME $REP"
echo $TEST | ./$NAME $REP | cat -e

echo ""
echo "Testing no args"
./$NAME

echo ""
echo "Testing 2 args"
./$NAME "a" "b"

rm $NAME
