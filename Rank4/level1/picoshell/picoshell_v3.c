#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static void super_dup2(int fd, int target_fd)
{
	if (dup2(fd, target_fd) == -1)
		exit(1);
	close(fd);
}

static void exec_child(char **cmd, int fds[2], int prev_fd, int has_next)
{
	if (prev_fd != -1)
		super_dup2(prev_fd, STDIN_FILENO);
	if (has_next)
	{
		close(fds[0]);
		super_dup2(fds[1], STDOUT_FILENO);
	}
	execvp(cmd[0], cmd);
	exit(1);
}

int picoshell(char **cmds[])
{
	int i = 0;
	int fds[2];
	int prev_fd = -1;
	pid_t pid;

	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(fds) == -1)
			return 1;
		
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1]) { close(fds[0]); close(fds[1]); }
			if (prev_fd != -1) close(prev_fd);
			return 1;
		}

		if (pid == 0)
			exec_child(cmds[i], fds, prev_fd, !!cmds[i + 1]); // !! sirve para devolver un bool a la funcion si existe el comando siguiente o no)

		if (prev_fd != -1)
			close(prev_fd);

		if (cmds[i + 1])
		{
			close(fds[1]);
			prev_fd = fds[0];
		}
		i++;
	}
	
	int status;
	int exit_code = 0;

	while(wait(&status) > 0)
	{ 
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_code = 1;
		else if (!WIFEXITED(status))
			exit_code = 1;
	}
	
	return (exit_code);
}
