echo testing echo
echo -n hola
echo ----n hola
echo -n-n-n hola
echo -nnnnNnnnnnnnnn hola

pwd
cd src
pwd
cd ..
pwd

echo echo hola | ./minishell

export TEST=hola
export | grep "TEST"
env | grep "TEST"
unset TEST
export | grep "T"


echo
echo "hola mundo"
echo -n hola mundo
echo "-n" hola mundo
echo hola mundo -n
echo -n -n hola
echo -nnnnnnn hola
echo -n-n hola
echo "a""b""c"
echo hola     mundo      separados
echo -ne "Hola\nMundo"

 
########################################
1. Compilación (más detallado)

make -n | grep -E "Wall|Wextra|Werror"
make clean && ls -la
make && ls -la
touch src/main.c && make
rm -f minishell && make


2. Comandos simples y variables globales (más complejos)

/bin/ls
/usr/bin/find / -name "*.h" -type f 2>/dev/null | /usr/bin/head -n 5
/bin/cat /proc/sys/kernel/hostname
/usr/bin/du -sh /etc
                     (varios espacios y tabs)
/bin/echo -e "\033[31mTexto en rojo\033[0m"
/bin/sleep 3


3. Argumentos (casos más complejos)

/bin/ls -la --color=auto /etc /var
/bin/grep -r --include="*.h" "malloc" /usr/include
/usr/bin/find /tmp -type f -mtime -1 -ls
/bin/ps aux | /bin/grep bash
/usr/bin/curl -s https://api.ipify.org
/bin/echo -e "Línea1\nLínea2\tTabulado"
/bin/ls -a-l-t
/bin/ls archivo\ con\ espacios


4. echo (casos especiales)

echo
echo "hola mundo"
echo -n hola mundo
echo "-n" hola mundo
echo hola mundo -n
echo -n -n hola
echo -nnnnnnn hola
echo -n-n hola
echo "a""b""c"
echo hola     mundo      separados
echo -ne "Hola\nMundo"


5. exit (casos límite)

exit
exit 0
exit 42
exit -42
exit 2147483647
exit -2147483648
exit 9223372036854775807
exit -9223372036854775808
exit 9223372036854775808
exit -9223372036854775809
exit +100
exit ++100
exit +++100
exit --100
exit exit
exit 42 53 64
exit hola mundo
exit 42hola


6. Valor de retorno (casos avanzados)

ls archivo_que_no_existe
echo $?
/bin/bash -c "exit 157"
echo $?
(exit 123)
echo $?
false
echo $?
true
echo $?
echo "El valor es $?"
echo $? $? $?
echo $(echo $?)
echo $((5 + $?))


7. Señales (pruebas más exhaustivas)

sleep 60                 (y luego Ctrl+C)
cat                      (y luego Ctrl+C)
cat                      (y luego Ctrl+D)
cat                      (y luego Ctrl+\)
yes                      (y luego Ctrl+C)
ping localhost           (y luego Ctrl+C)
grep "algo"              (y luego Ctrl+\)
while true; do echo hi; sleep 1; done       (y luego Ctrl+C)
cat /dev/urandom         (y luego Ctrl+C)


8. Comillas dobles (casos complicados)

echo "Hola \"escapado\" mundo"
echo "Usuario: $USER, Home: $HOME"
echo "Texto con varios     espacios"
echo "Texto con caracteres especiales: !@#$%^&*()"
echo "Texto con redirección: > >> < <<"
echo "Texto con pipes: | |"
echo "Texto $USER con $VARIABLE_INEXISTENTE variables"
echo "Texto"" concatenado"
echo """"""
echo ";"
echo "&&"
echo "||"
echo "texto con
salto de línea"
echo "*"


9. Comillas simples (casos complicados)

echo 'Hola \'escapado\' mundo'
echo 'Usuario: $USER, Home: $HOME'
echo 'Texto con varios     espacios'
echo 'Texto con caracteres especiales: !@#$%^&*()'
echo 'Texto con redirección: > >> < <<'
echo 'Texto con pipes: | |'
echo 'Texto $USER con $VARIABLE_INEXISTENTE variables'
echo 'Texto'' concatenado'
echo ''''''
echo ';'
echo '&&'
echo '||'
echo 'texto con
salto de línea'
echo '*'


10. env (pruebas más específicas)

env
env | grep PATH
env | sort
env | wc -l
env | grep -v "="
env NUEVO=valor
env -i


11. export (casos avanzados)

export
export VARIABLE=valor
export | grep "VARIABLE"
export VARIABLE+=añadido
export PRUEBA="texto con espacios"
export VAR1=1 VAR2=2 VAR3=3
export COMBINADA="$USER:$HOME"
export EMPTY=""
export RUTA="$PATH:/nuevo/directorio"
export 123VAR=valor
export VAR.PUNTO=valor
export VAR@ARROBA=valor
export VAR$DOLAR=valor
export --help
export -p


12. unset (más complejo)

export TEMP1=uno TEMP2=dos TEMP3=tres
env | grep TEMP
unset TEMP1
env | grep TEMP
unset TEMP2 TEMP3
env | grep TEMP
unset PATH
ls
unset INEXISTENTE
unset USER HOME
unset
unset -n
unset --help


13. cd (casos avanzados)

pwd
cd /
pwd
cd /etc
pwd
cd ..
pwd
cd /tmp
pwd
cd .
pwd
cd ~
pwd
cd $HOME
pwd
cd -
pwd
cd ~/directorio_que_no_existe
mkdir -p $HOME/test/subdir
cd $HOME/test/subdir
pwd
cd ../..
pwd
cd //
pwd
cd /./././
pwd


14. pwd (casos complejos)

pwd
cd /tmp
pwd
cd "$HOME"
pwd
mkdir -p $HOME/test/a/b/c
cd $HOME/test/a/b/c
pwd
cd ../../../..
pwd
cd /proc/self
pwd
cd ///
pwd
cd /usr//bin/
pwd


15. Ruta relativa (más complicado)

cd $HOME
./minishell
cd ..
./*/minishell
cd $HOME
../../../bin/ls
cd /usr/bin
../../etc/passwd
./ls ../../tmp/
cd $HOME
../../../../../../../bin/echo hola
ls ./././


16. Path de entorno (casos especiales)

echo $PATH
ls
which ls
export PATH=/bin:/usr/bin
ls
export PATH=/usr/bin:/bin
ls
export PATH=/usr/games:/usr/bin:/bin
ls
export PATH=
ls
/bin/ls
export PATH=/directorio_que_no_existe:/bin
ls
export PATH="/bin:/tmp:$HOME:$HOME/bin"
ls
export PATH=".:$PATH"
touch ejecutable.sh && chmod +x ejecutable.sh && echo "echo funciona!" > ejecutable.sh
./ejecutable.sh
ejecutable.sh


17. Redirecciones (más complejos)

ls > archivo1.txt
cat archivo1.txt
ls >> archivo1.txt
cat archivo1.txt
wc -l < /etc/passwd
ls > archivo1.txt > archivo2.txt > archivo3.txt
echo "hola" > archivo4.txt >> archivo5.txt
cat no_existe 2> errores.txt
cat archivo1.txt archivo2.txt > combinado.txt
echo "sobrescribir" > archivo1.txt
cat archivo1.txt
echo "datos " > archivo.tmp && echo "más datos" >> archivo.tmp
cat < archivo.tmp > copia.tmp
> nuevo_vacio.txt
>>>> muchos.txt
ls > /dev/null
ls -la > archivo.txt 2> errores.txt
cat << DELIMITADOR
Esto es un texto
que tiene varias lineas
y termina en
DELIMITADOR
cat << "FIN"
$USER
`ls`
$(pwd)
FIN
cat << 'FIN'
$USER
`ls`
$(pwd)
FIN
cat << FIN > salida_heredoc.txt
Esto va a un archivo
FIN


18. Pipes (casos complejos)

ls | grep .txt
cat /etc/passwd | grep root | wc -l
echo "hola mundo" | cat | cat | cat | cat
ls -la | grep "^d" | sort -r | head -n 3
ls archivo_que_no_existe | grep algo
ls | ls | ls | ls
cat /etc/passwd | grep -v root | grep -v daemon | wc -l
(ls -la | grep "^d") | wc -l
echo hola | (cat | cat) | cat
ls | grep ".txt" | tee archivo.txt | wc -l
find /etc -type f 2>/dev/null | grep conf | sort | uniq -c | sort -nr | head -n 5
yes | head -n 5
ps aux | grep bash | grep -v grep | awk '{print $2}'
cat < archivo1.txt | grep texto | tee archivo2.txt | wc -l
ls -la | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat


19. Variables de entorno (casos avanzados)

echo $USER
echo "Mi usuario es $USER y mi home es $HOME"
echo '$USER no se expande, pero $HOME tampoco'
echo "Variable inexistente: $NOEXISTE"
echo ${USER}
echo $USER$HOME
echo "$USER""$HOME"
echo $USER_INVALID
echo "Variable con espacio: $VAR_CON_ESPACIO"
export VAR='$USER'
echo $VAR
export VAR="$USER"
echo $VAR
echo $?
echo $$ # PID del shell
echo $0
Bonus (si aplica)
And, Or (casos extremos)



ls && echo "éxito"
ls archivo_que_no_existe && echo "no se ve"
ls || echo "no se ve"
ls archivo_que_no_existe || echo "se ve"
true && echo "éxito" || echo "fallo"
false && echo "no se ve" || echo "se ve"
ls && ls && ls && ls && echo "todos exitosos"
ls && ls archivo_que_no_existe && ls && ls
ls || ls || ls || ls
ls archivo_que_no_existe || echo "recuperación" && echo "continúa"
(ls && echo "dentro de paréntesis") && echo "fuera de paréntesis"
(ls archivo_que_no_existe || echo "recuperado") && echo "continúa"
false || (true && echo "esto se ve")
true && (false || echo "esto también")
true && true || false && false
false && false || true && true
(ls && echo a) && (ls && echo b) || (ls && echo c)
Wildcard (casos complejos)



echo *
ls *.txt
ls .*
ls */*
ls ../*
echo *.???
mkdir -p testdir && touch testdir/file{1..5}.txt
ls testdir/*.txt
ls [a-z]*
ls [A-Z]*
ls [0-9]*
ls ?????
ls *[!0-9]
Prueba de interpretación (complicadas)



export USER=estudiante42
echo "'$USER'"
echo '"$USER"'
echo "\"$USER\""
echo '\''$USER'\'''
echo "\$USER"
echo '\$USER'
export COMPLICADO="un'texto\"con$caracteres"
echo "$COMPLICADO"
echo '$COMPLICADO'
echo "'$COMPLICADO'"
echo '"$COMPLICADO"'