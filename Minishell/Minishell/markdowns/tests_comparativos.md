# Minishell vs Bash Comparison Tests

Run the following commands in both `bash` and your `minishell` to compare behavior. Check standard output, standard error, exit codes (`echo $?`), and file system changes.

## Simple Commands & Arguments
1. `ls`
2. `ls -la`
3. `/bin/ls`
4. `echo simple text`
5. `echo -n no_newline_here`
6. `sleep 1`

## Builtins (Environment & State)
7. `pwd`
8. `cd ..` followed by `pwd`
9. `cd /` followed by `pwd`
10. `export MY_VAR=hello` followed by `echo $MY_VAR`
11. `export MY_VAR=updated` followed by `env | grep MY_VAR`
12. `unset MY_VAR` followed by `env | grep MY_VAR`
13. `env`
14. `exit 42` (Check exit code in parent shell)

## Pipes
15. `ls | wc -l`
16. `cat /etc/passwd | head -n 5`
17. `yes | head -n 10`
18. `ls | grep "M" | wc -l`
19. `ls -la | grep .c | wc -l`
20. `echo hello | cat | cat`

## Redirections (Input/Output/Append)
21. `echo "test file" > test_file.txt` followed by `cat test_file.txt`
22. `echo "append this" >> test_file.txt` followed by `cat test_file.txt`
23. `wc -l < test_file.txt`
24. `ls -la > listing.txt`
25. `sort < listing.txt`
26. `cat < Makefile > copy_makefile.txt`

## Heredoc (<<)
27. `cat << EOF` (Input `line1`, `line2`, `EOF`)
28. `grep "a" << END` (Input `apple`, `banana`, `cherry`, `diff`, `END`)
29. `wc -l << TERMINATOR` (Input multiple lines, then `TERMINATOR`)

## Logical Operators (&& and ||)
30. `echo true && echo executed`
31. `echo true || echo ignored`
32. `ls nowhere || echo "ls failed, this runs"`
33. `ls Makefile && echo "found makefile"`
34. `false && echo skipped`
35. `false || echo recovered`

## Complex Pipes & Redirections
36. `ls -la | grep .c > c_files.txt`
37. `cat < c_files.txt | wc -l >> counts.txt`
38. `head -n 2 Makefile | grep "N" > out_pipe.txt`
39. `echo "start" > file1 && cat file1 | wc -w`

## Quotes & Expansion
40. `echo "$USER"`
41. `echo '$USER'`
42. `echo "'$USER'"`
43. `echo '"$USER"'`
44. `export A=B && export B=C && echo $A`

## Error Handling
45. `computadora_que_no_existe` (Should print command not found)
46. `ls | comando_falso`
47. `cat archivo_que_no_existe`
48. `cd carpeta_que_no_existe`

## Edge Cases
49. `cat | cat | ls`
50. `      ls      -l      ` (Spaces handling)
