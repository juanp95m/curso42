cat testeoecho.sh | bash > bash_tests.txt
cat testeoecho.sh | ./minishell > mini_tests.txt

diff bash_tests.txt mini_tests.txt

rm bash_tests.txt 
rm mini_tests.txt