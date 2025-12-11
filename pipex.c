/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:09:32 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 18:28:41 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_pipe(int fd_in, int fd_out, char **command1, char **command2)
{
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	if (command1)
		free_split(command1);
	if (command2)
		free_split(command2);
}

static int	files_init(char **av, int *fd_in, int *fd_out)
{
	*fd_in = open(av[1], O_RDONLY);
	if (*fd_in == -1)
	{
		perror("Error opening input file.");
		return (0);
	}
	*fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		perror("Error opening output file.");
		if (*fd_in != -1)
			close(*fd_in);
		return (0);
	}
	return (1);
}

static int	init_commands(char **av, char **command[])
{
	command[0] = ft_split(av[2], ' ');
	command[1] = ft_split(av[3], ' ');
	if (!command[0] || !command[0][0] || !command[1] || !command[1][0])
	{
		ft_putendl_fd("Error: Invalid command arguments", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	char	**command[2];
	int		pid1;
	int		pid2;
	int		pipefd[2];
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile",
				STDERR_FILENO), 1);
	if (!files_init(av, &fd_in, &fd_out))
		return (1);
	if (!init_commands(av, command))
		return (clean_pipe(fd_in, fd_out, command[0], command[1]), perror("pipe"), 1);
	if (pipe(pipefd) == -1)
		return (clean_pipe(fd_in, fd_out, command[0], command[1]), 1);
	pid1 = fork();
	if (pid1 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (clean_pipe(fd_in, fd_out, command[0], command[1]),
			perror("fork"), 1);
	}
	if (pid1 == 0)
		child_process(pipefd, fd_in, command, envp);
	pid2 = fork();
	if (pid2 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (clean_pipe(fd_in, fd_out, command[0], command[1]),
			perror("fork"), 1);
	}
	if (pid2 == 0)
		parent_process(pipefd, fd_out, command, envp);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_split(command[0]);
	free_split(command[1]);
	return (0);
}
