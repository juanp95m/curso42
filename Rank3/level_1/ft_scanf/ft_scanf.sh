if [ -z "$1" ]; then
    echo "Usage: $0 <source_file.c>"
    exit 1
fi

cc -Wall -Wextra -Werror "$1" -o ft_scanf
echo ">>Testing ./ft_scanf with 'a 42 Hello'"
echo "a 42 Hello" | ./ft_scanf | cat -e
rm ft_scanf
