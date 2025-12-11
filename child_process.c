/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:27:29 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 20:03:10 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command_with_path(char *path, char **command[], char **envp)
{
	check_file_access(path, command[0]);
	execve(path, command[0], envp);
	free(path);
	perror("execve failed");
	handle_command(command[0], NULL, EXIT_FAILURE);
}

void	child_process(int *pipefd, int fd_in, char **command[], char **envp)
{
	char	*path1;

	close(pipefd[0]);
	if (!command[0] || !command[0][0])
	{
		ft_putendl_fd("Error: First command is empty", STDERR_FILENO);
		handle_command(command[0], NULL, 127);
	}
	if (fd_in == -1)
	{
		close(pipefd[1]);
		ft_putendl_fd("Error: Input file error", STDERR_FILENO);
		handle_command(command[0], NULL, 1);
	}
	dup_and_close(fd_in, pipefd[1]);
	path1 = get_path(command[0][0], envp);
	if (path1 == NULL)
	{
		print_command_error(command[0][0]);
		handle_command(command[0], NULL, 127);
	}
	execute_command_with_path(path1, command, envp);
}
