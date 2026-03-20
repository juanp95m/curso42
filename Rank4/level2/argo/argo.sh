#!/bin/bash
NAME=$(basename "$1" .c)
cc -Wall -Wextra -Werror "$1" -o "$NAME"

echo "Testing $NAME..."
# Using the tests from subject
echo -n '1' | ./$NAME /dev/stdin | cat -e
echo -n '"bonjour"' | ./$NAME /dev/stdin | cat -e
echo -n '"escape! \" "' | ./$NAME /dev/stdin | cat -e
echo -n '{"tomatoes":42,"potatoes":234}' | ./$NAME /dev/stdin | cat -e
echo -n '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' | ./$NAME /dev/stdin | cat -e
echo -n '"unfinished string' | ./$NAME /dev/stdin | cat -e
echo -n '"unfinished string 2\"' | ./$NAME /dev/stdin | cat -e
echo -n '{"no value?":}' | ./$NAME /dev/stdin | cat -e

rm "$NAME"
