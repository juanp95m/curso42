cc -Wall -Wextra -Werror scanf.c -o scanf
echo ">>Testing ./scanf with 'a 42 Hello'"
echo "a 42 Hello" | ./scanf | cat -e
rm scanf
