echo hello | cat
echo hello | cat | cat
echo hello | wc -c
printf "b\na\nc\n" | sort
/bin/ls /dev/null | cat
echo "apple banana cherry" | tr ' ' '\n' | sort
echo "abc" | rev | rev
echo "line1" > /tmp/ms_complex_a.txt
echo "line2" >> /tmp/ms_complex_a.txt
echo "line3" >> /tmp/ms_complex_a.txt
cat /tmp/ms_complex_a.txt | wc -l
cat /tmp/ms_complex_a.txt | grep "line" | wc -l
cat /tmp/ms_complex_a.txt | sort -r > /tmp/ms_complex_b.txt
cat /tmp/ms_complex_b.txt
ls /tmp/ms_complex_a.txt | wc -l
rm /tmp/ms_complex_a.txt /tmp/ms_complex_b.txt


ls | wc
ls|wc
sort colors.txt | uniq | sort -r | wc
|
"" | ""