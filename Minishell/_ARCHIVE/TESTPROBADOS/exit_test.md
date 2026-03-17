
# Exit commands

## Bash
```
$>exit
$>echo $?
0
$>exit 0
$>echo $?
0
$>exit 42
$>echo $?
42
$>exit -42
$>echo $?
214
$>exit 2147483647
$>echo $?
255
$>exit -2147483648
$>echo $?
0
$>exit 9223372036854775807
$>echo $?
255
$>exit -9223372036854775808
$>echo $?
0
$>exit 9223372036854775808
$>echo $?
exit
bash: exit: 9223372036854775808: numeric argument required
2
$>exit -9223372036854775809
$>echo $?
exit
bash: exit: -9223372036854775809: numeric argument required
2
$>exit +100
$>echo $?
100
$>exit ++100
$>echo $?
2
$>exit +++100
$>echo $?
2
$>exit --100
$>echo $?
2
$>exit exit
$>echo $?
2
$>exit 42 53 64
$>echo $?
1
$>exit hola mundo
$>echo $?
2
$>exit 42hola
$>echo $?
2
```

## Minishell
```
$>exit
$>echo $?
0
$>exit 0
$>echo $?
0
$>exit 42
$>echo $?
42
$>exit -42
$>echo $?
214
$>exit 2147483647
$>echo $?
255
$>exit -2147483648
$>echo $?
0
$>exit 9223372036854775807
$>echo $?
255
$>exit -9223372036854775808
$>echo $?
0
$>exit 9223372036854775808
$>echo $?
exit
minishell: exit: 9223372036854775808: numeric argument required
2
$>exit -9223372036854775809
$>echo $?
exit
minishell: exit: -9223372036854775809: numeric argument required
2
$>exit +100
$>echo $?
100
$>exit ++100
$>echo $?
2
$>exit +++100
$>echo $?
2
$>exit --100
$>echo $?
2
$>exit exit
$>echo $?
2
$>exit 42 53 64
$>echo $?
1
$>exit hola mundo
$>echo $?
2
$>exit 42hola
$>echo $?
2
```