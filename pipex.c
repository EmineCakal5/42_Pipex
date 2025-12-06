/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:09:32 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/06 03:51:15 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_command(char **command1, char **command2)
{
	free_split(command1);
	free_split(command2);
	exit(127);
}

static void	dup_and_close(int fd_in, int out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(fd_in);
	close(out);
}
static void	child_process(int *pipefd, int fd_in, char **command[], char **envp)
{
	char	*path1;

	close(pipefd[0]);
	if (!command[0] || !command[0][0])
		handle_command(command[0], command[1]);
	if (fd_in == -1)
	{
		close(pipefd[1]);
		handle_command(command[0], command[1]);
	}
	if (command[0] != NULL)
	{
		dup_and_close(fd_in, pipefd[1]);
		path1 = get_path(command[0][0], envp);
		if (path1 == NULL)
		{
			perror("First command is invalid");
			handle_command(command[0], command[1]);
		}
		execve(path1, command[0], envp);
		free(path1);
		free_split(command[0]);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

static void	parent_process(int *pipefd, int fd_out, char **command[],
		char **envp)
{
	char	*path2;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipefd[0]);
	close(fd_out);
	if (!command[1] || !command[1][0])
	{
		free_split(command[1]);
		exit(127);
	}
	path2 = get_path(command[1][0], envp);
	if (path2 == NULL)
	{
		handle_command(command[0], command[1]);
		perror("Second command is invalid");
	}
	execve(path2, command[1], envp);
	free(path2);
	free_split(command[1]);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

static int	files_init(char **av, int *fd_in, int *fd_out)
{
	*fd_in = open(av[1], O_RDONLY);
	if (*fd_in == -1)
		perror("Error opening input file.");
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

int	main(int ac, char **av, char **envp)
{
	char	**command[2];
	int		pid;
	int		pipefd[2];
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (1);
	if (!files_init(av, &fd_in, &fd_out))
		return (1);
	command[0] = ft_split(av[2], ' ');
	command[1] = ft_split(av[3], ' ');
	if (pipe(pipefd) == -1 || !command[1][0])
		return (clean_pipe(fd_in, fd_out, command[0], command[1]), 1);
	pid = fork();
	if (pid == 0)
		child_process(pipefd, fd_in, command, envp);
	else if (pid > 0)
	{
		close(fd_in);
		waitpid(pid, NULL, 0);
		parent_process(pipefd, fd_out, command, envp);
	}
	return (0);
}
