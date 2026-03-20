#!/bin/bash
NAME=$(basename "$1" .c)
cc -Wall -Wextra -Werror "$1" main.c -o "$NAME"

echo "Testing $NAME..."
# ./"$NAME"
valgrind --leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--track-fds=yes \
--trace-children=yes \
--suppressions=picoshell.supp \
# --log-file=valgrind_report.log \
./"$NAME"

rm "$NAME"