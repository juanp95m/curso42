#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

void redirect(int oldfd, int newfd)
{
	if (oldfd != -1)
	{
		if (dup2(oldfd, newfd) == -1)
			exit(1);
		close(oldfd);
	}
}

void child_process(char **cmd, int is_last, int fd[2], int last_fd)
{
	redirect(last_fd, STDIN_FILENO);
	if (!is_last)
	{
		close(fd[0]);
		redirect(fd[1], STDOUT_FILENO);
	}
	execvp(cmd[0], cmd);
	exit(1);
}

int wait_all()
{
	int status, exit_code = 0;
	while (wait(&status) > 0)
	{
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			exit_code = 1;
	}
	return (exit_code);
}

int picoshell(char **cmds[])
{
	int fd[2], last_fd = -1;
	
	for (int i = 0; cmds[i]; i++)
	{
		int is_last = (cmds[i + 1] == NULL);
		if (!is_last && pipe(fd) == -1)
			return (1);
		pid_t pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			child_process(cmds[i], is_last, fd, last_fd);
		if (last_fd != -1)
			close(last_fd);
		if (!is_last)
		{
			close(fd[1]);
			last_fd = fd[0];
		}
	}
	return (wait_all());
}
