./minishell
exit
echo $?
./minishell
exit 0
echo $?
./minishell
exit 42
echo $?
./minishell
exit -42
echo $?
./minishell
exit 2147483647
echo $?
./minishell
exit -2147483648
echo $?
./minishell
exit 9223372036854775807
echo $?
./minishell
exit -9223372036854775808
echo $?
./minishell
exit 9223372036854775808
echo $?
./minishell
exit -9223372036854775809
echo $?
./minishell
exit +100
echo $?
./minishell
exit ++100
echo $?
./minishell
exit +++100
echo $?
./minishell
exit --100
echo $?
./minishell
exit exit
echo $?
./minishell
exit 42 53 64
echo $?
./minishell
exit hola mundo
echo $?
./minishell
exit 42hola
echo $?