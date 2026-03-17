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
rm -rf /tmp/ms_wildcard_test

echo hola > out1
cat out1
echo caracola >> out1
cat out1
echo hola > out1 > out2 > out3
ls out*
cat < colors.txt
cat < colors.txt > copia.txt
cat copia.txt
cat colors.txt | wc