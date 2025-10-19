#include "fcntl.h"
#include "stdio.h"
#include "sys/wait.h"
#include "unistd.h"
#include "stdlib.h"
#include "libft/libft.h"

char *get_path(char *av, char **env);

int main(int ac, char **av, char **envp)
{
	int fd_in = open(av[1], O_RDONLY , 0644);
	if (fd_in == -1)
	{
		perror("Error opening input file.");
		return 1;
	}
	int fd_out = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR , 0644 );
	if (fd_out == -1)
	{
		perror("Error opening input file.");
		return 1;
	}

	int pid;
	int fd[2];
	int prev_fd = -1;
	int i = 0;

	while (i < ac - 3)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(fd_in, 0);
			}
			else
				dup2(prev_fd, 0);
			if (i == ac - 4)
			{
				dup2(fd_out, 1);
			}
			else
				dup2(fd[1], 1);
			char **command = ft_split(av[i+1], ' ');
			char *path = get_path(command[0], envp);
			execve(path, command, envp);
		}
		else
		{
			wait(NULL);
			if (prev_fd != -1)
				close(prev_fd);
			close(fd[1]);
			prev_fd = fd[0];
		}
		i++;
	}
	close(fd_in);
	close(fd_out);
	while (i > 0)
	{
		wait(NULL);
		i--;
	}
}