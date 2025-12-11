/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:00:00 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 19:51:03 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	files_init(char **av, int *fd_in, int *fd_out)
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

int	init_commands(char **av, char **command[])
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

int	fork_child(int *pipefd, int fd_in, char **command[], char **envp)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		return (-1);
	}
	if (pid1 == 0)
		child_process(pipefd, fd_in, command, envp);
	return (pid1);
}

int	fork_parent(int *pipefd, int fd_out, char **command[], char **envp)
{
	int	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		perror("fork");
		return (-1);
	}
	if (pid2 == 0)
		parent_process(pipefd, fd_out, command, envp);
	return (pid2);
}
