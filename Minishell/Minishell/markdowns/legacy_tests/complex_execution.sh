
ls -la | grep .c > c_files.txt
cat < c_files.txt | wc -l >> counts.txt
head -n 2 Makefile | grep "N" > out_pipe.txt
echo "start" > file1 && cat file1 | wc -w

rm c_files.txt counts.txt out_pipe.txt file1
