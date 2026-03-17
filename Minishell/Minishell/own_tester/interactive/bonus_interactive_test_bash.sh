export _MSDIR=$PWD
echo "red" > colors.txt
echo "green" >> colors.txt
echo "blue" >> colors.txt
echo "yellow" >> colors.txt
echo hello
echo -n noeol
echo -n
echo hello world
echo ""
echo "  spaces  "
echo -n one -n two
echo one two   three
echo 
echo "" hola
echo -n -n hola
echo -n -nh -n hola
echo -nnnnnnnnn hola
echo 'echo "hola'
echo $?hcudshfuewrf ew  wr 4ew""""
echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'f'f'f''f'f'f'f'f'f'
echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'a'j'o''i'w'q''q
echo ""aaaaaaaa"bbbbb"'''' ccccccccc "dddddddd"e'e'e
echo "ho   $USER"  'la   $LESS'   $USER$TERM
echo "ho   $USER"'la   $LESS'$USER$TERM
echo"ho   $USER"
echo"ho   $USE$LESS"
"echo" "ho   $USER"
e"cho" "ho   $USER"
       echo "ho   $USER"
echo "$HOME '$LESS' $USER"
echo '$HOME "$LESS" $USER'
echo '$'"HOME"

pwd
cd /tmp
pwd
cd /
pwd
cd /usr/bin
pwd
cd ..
pwd
cd .
pwd
cd /nonexistent_directory_xyz
echo $?
cd $_MSDIR
export _SAVED_HOME=$HOME
unset HOME
cd
echo $?
export HOME=$_SAVED_HOME
unset _SAVED_HOME
cd $_MSDIR
cd -
pwd
cd ~
pwd
cd $_MSDIR

echo '$USER'
echo '$?'
echo 'hello world'
echo ''
echo 'no | pipe here'
echo 'no > redirect'
echo 'spaces   preserved'
echo '$USER is not expanded in single quotes'
echo "hello world"
echo "spaces   preserved"
echo "cat lol.c | cat > lol.c"
export DQTEST=expanded
echo $DQTEST
echo "$DQTEST"
echo "value is $DQTEST end"
echo "$?"
echo "'$USER'"
echo '"$USER"'
echo "$COMPLICADO"
echo '$COMPLICADO'
echo "'$COMPLICADO'"
echo '"$COMPLICADO"'

echo "first line" > /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
echo "second line" >> /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
echo "third line" >> /tmp/ms_test_redir.txt
wc -l < /tmp/ms_test_redir.txt
echo "overwrite" > /tmp/ms_test_redir.txt
cat /tmp/ms_test_redir.txt
rm /tmp/ms_test_redir.txt
echo hola > /tmp/ms_rout1.txt
cat /tmp/ms_rout1.txt
echo caracola >> /tmp/ms_rout1.txt
cat /tmp/ms_rout1.txt
echo hola > /tmp/ms_rout1.txt > /tmp/ms_rout2.txt > /tmp/ms_rout3.txt
cat /tmp/ms_rout1.txt
cat /tmp/ms_rout2.txt
cat /tmp/ms_rout3.txt
rm -f /tmp/ms_rout1.txt /tmp/ms_rout2.txt /tmp/ms_rout3.txt

cat << EOF
line one
line two
line three
EOF
grep "an" << WORDS
apple
banana
cherry
mango
WORDS
wc -l << COUNTER
a
b
c
d
e
COUNTER

echo hello | cat
echo hello | cat | cat
echo hello | wc -c
/bin/ls /dev/null | cat
echo "apple banana cherry" | tr ' ' '\n' | sort
echo "abc" | rev | rev
echo "line1" > /tmp/ms_pipe_a.txt
echo "line2" >> /tmp/ms_pipe_a.txt
echo "line3" >> /tmp/ms_pipe_a.txt
cat /tmp/ms_pipe_a.txt | wc -l
cat /tmp/ms_pipe_a.txt | grep "line" | wc -l
cat /tmp/ms_pipe_a.txt | sort -r > /tmp/ms_pipe_b.txt
cat /tmp/ms_pipe_b.txt
rm /tmp/ms_pipe_a.txt /tmp/ms_pipe_b.txt
mkdir test_ls_pipe_wc
cd test_ls_pipe_wc
touch file1 file2 file3
ls | wc
ls|wc
cd ..
rm -rf test_ls_pipe_wc
wc < colors.txt > /tmp/ms_wc_out.txt
cat /tmp/ms_wc_out.txt
rm -f /tmp/ms_wc_out.txt
cat colors.txt | wc

export TESTVAR=hello42
echo $TESTVAR
export TESTVAR=updated
echo $TESTVAR
echo $?
unset TESTVAR
echo $TESTVAR
export MY_VAR=hello
echo $MY_VAR
env | grep MY_VAR
export MY_VAR=updated
echo $MY_VAR
env | grep MY_VAR
unset MY_VAR
echo $MY_VAR
echo "exit:$?"
export A=1
echo $A
export B=2
echo $B
export C=3
echo $C
unset B
echo $A
echo $B
echo $C
env | grep -E "^A=|^B=|^C=" | sort
export a=b
echo $a
export b=wawa
echo $b
export b=lala
echo $b
export c=lala=kaka
echo $c
export a=
echo "|$a|"
export a3=l
echo $a3
export 2a=lala
export NUEVA=$TERM
echo $NUEVA
export POLLOS=asados
echo $POLLOS
unset POLLOS
echo $POLLOS
export A=1 B=2
echo $A $B
unset A B
echo $A $B
export a= b=o
echo $a $b
export a===
echo $a
export ""
env
env lalal
env directorio
unset
unset $HOME $USER

mkdir -p /tmp/ms_wildcard_test
echo "c file" > /tmp/ms_wildcard_test/foo.c
echo "h file" > /tmp/ms_wildcard_test/foo.h
echo "txt file" > /tmp/ms_wildcard_test/bar.txt
cd /tmp/ms_wildcard_test
echo *.c
echo *.h
echo *.txt
ls *.c
ls *.h
echo *
cd $_MSDIR
rm -rf /tmp/ms_wildcard_test
cat < colors.txt
cat < colors.txt > copia.txt
cat copia.txt
rm -f copia.txt
cat colors.txt | wc

echo "extra" > /tmp/ms_logic_a.txt && cat /tmp/ms_logic_a.txt
echo one && echo two
true && echo "true_passed"
false && echo "SHOULD_NOT_PRINT"
false || echo "false_recovered"
true || echo "SHOULD_NOT_PRINT"
echo "start" && false || echo "fallback"
false || false || echo "last_resort"
true && true && echo "all_true"
false || true && echo "chain_ok"
(echo uno && (false || echo dos)) && echo tres
(false && echo "nope") || (true && echo "ok")
(echo "A" && (false || (echo "B" && true))) || echo "C"
(true && (false || (true && echo "deep"))) && echo "final"
(echo "start" && (false || (echo "mid" && false)) && echo "never") || echo "end"
(false || (false && echo "no") || (true && echo "yes")) && echo "done"
mkdir test_ls_bool
cd test_ls_bool
touch file1 file2 file3
ls && echo "exito"
ls archivo_que_no_existe && echo "no se ve"
ls || echo "no se ve"
ls archivo_que_no_existe || echo "se ve"
true && echo "exito" || echo "fallo"
false && echo "no se ve" || echo "se ve"
ls && ls && ls && ls && echo "todos exitosos"
ls && ls archivo_que_no_existe && ls && ls
ls || ls || ls || ls
ls archivo_que_no_existe || echo "recuperacion" && echo "continua"
(ls && echo "dentro de parentesis") && echo "fuera de parentesis"
(ls archivo_que_no_existe || echo "recuperado") && echo "continua"
false || (true && echo "esto se ve")
true && (false || echo "esto tambien")
true && true || false && false
false && false || true && true
(ls && echo a) && (ls && echo b) || (ls && echo c)
cd ..
rm -rf test_ls_bool
rm -f /tmp/ms_logic_a.txt

mkdir -p /tmp/ms_lperalta_test
mkdir -p /tmp/ms_lperalta_test/dir_existe
touch /tmp/ms_lperalta_test/file_existe
mkdir -p /tmp/ms_lperalta_test/dir_noperm
chmod 000 /tmp/ms_lperalta_test/dir_noperm
echo -e "red\ngreen\nblue\nyellow" > /tmp/ms_lperalta_test/colors.txt
cd /tmp/ms_lperalta_test
echo $?hcudshfuewrf ew  wr 4ew""
echo "ho   $USER"  "la   $LESS"   $USER$TERM
echo "ho   $USER"
echo"ho   $USER"
e"cho" "ho   $USER"
       echo "ho   $USER"
echo "$HOME" "$USER"
cd dir_existe
pwd
cd directorio_no_existe
echo $?
cd file_existe
echo $?
cd /tmp/ms_lperalta_test
cd
pwd
ls | wc
ls|wc
echo "colorinchis" > colors.txt
cat colors.txt | sort -r | wc
cd -
pwd
cd ~
pwd
cd $_MSDIR
chmod 755 /tmp/ms_lperalta_test/dir_noperm
rm -rf /tmp/ms_lperalta_test

export _SAVED_PATH=$PATH
unset PATH
ls
echo $?
/bin/ls
echo $?
export PATH=$_SAVED_PATH
unset _SAVED_PATH
ls noexiste
echo $?



bash --norc --noprofile
exit
echo $?
bash --norc --noprofile
exit 0
echo $?
bash --norc --noprofile
exit 42
echo $?
bash --norc --noprofile
exit -42
echo $?
bash --norc --noprofile
exit 2147483647
echo $?
bash --norc --noprofile
exit -2147483648
echo $?
bash --norc --noprofile
exit 9223372036854775807
echo $?
bash --norc --noprofile
exit -9223372036854775808
echo $?
bash --norc --noprofile
exit 9223372036854775808
echo $?
bash --norc --noprofile
exit -9223372036854775809
echo $?
bash --norc --noprofile
exit +100
echo $?
bash --norc --noprofile
exit ++100
echo $?
bash --norc --noprofile
exit +++100
echo $?
bash --norc --noprofile
exit --100
echo $?
bash --norc --noprofile
exit exit
echo $?
bash --norc --noprofile
exit 42 53 64
echo $?
bash --norc --noprofile
exit hola mundo
echo $?
bash --norc --noprofile
exit 42hola
echo $?

mkdir test_ls_syntax
cd test_ls_syntax
touch file1 file2 file3
ls || wc
ls |   | wc
| ls | wc
ls | wc |
echo "mensaje ignorado"
cd ..
rm -rf test_ls_syntax
rm colors.txt