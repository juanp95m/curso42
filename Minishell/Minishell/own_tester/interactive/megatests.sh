cat <<X <README.md  <README.md 10 bytes leaked
cat <README.md <README.md <README.md <README.md <<X 40 bytes leaked
cat <README.md <README.md <README.md <<X <README.md 70 bytes leaked

==2604787== 70 bytes in 7 blocks are definitely lost in loss record 19 of 68
==2604787==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==2604787==    by 0x4092E4: ft_strdup (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404FD7: parse_infile (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x40553D: dispatch_redirections (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404D35: handle_cmd_token (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404C8A: parse_simple_cmd (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404D74: parse_pipe (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404E44: parse_expression (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404F6C: parser (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x40495D: process_tokens_parser (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404A66: process_input (in /home/jperez-m/Minishell/Minishell/minishell)
==2604787==    by 0x404B1B: run_shell (in /home/jperez-m/Minishell/Minishell/minishell)


estamos teniendo leaks con estos comandos, al final se pone la cantidad de bytes perdidos
cat <<X <README.md  <README.md 10 bytes leaked
cat <README.md <README.md <README.md <README.md <<X 40 bytes leaked
cat <README.md <README.md <README.md <<X <README.md 70 bytes leaked
creo que puede deberse a un conflicto entre el fd abierto para el < y el <<, podrias confirmarlo (chequea ademas si podria pasar con append, yo sospecho que si porque outfiles tenemos un array y infile y append es un solo fd?) y si no, decirnos cual podria ser tu hipotesis.
