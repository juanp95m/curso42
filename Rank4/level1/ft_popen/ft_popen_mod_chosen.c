
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

void close_fds(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	int pid; // o pid_t
	int tp = (type == 'r') ? 1 : 0;
	if(!file || !argv || (type != 'r' && type != 'w'))
		return(-1);
	if(pipe(fd)== -1)
		return(-1);
	pid = fork();
	if(pid == -1)
	{
		close_fds(fd);
		return(-1);
	}
	if(pid == 0)
	{
		int fd_to_dup = tp ? fd[1] : fd[0];
		int std_target = tp ? STDOUT_FILENO : STDIN_FILENO;
		if(dup2(fd_to_dup, std_target) == -1)
			exit(1);
		close_fds(fd);
		execvp(file, argv);
		exit(1);
	}
	close(tp ? fd[1] : fd[0]);
	return(tp ? fd[0] : fd[1]);
}

