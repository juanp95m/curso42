cc -Wall -Wextra -Werror filter.c -o filter

TEST="jajrhabcjakrbakjcabc"
echo $TEST | ./filter abc
echo $1 | ./filter $2
echo 'abcdefaaaabcdeabcabcdabc' | ./filter abc | cat -e
echo 'ababcabababc' | ./filter ababc | cat -e

