/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:27:29 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 18:20:17 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	if (access(path1, F_OK) == -1)
	{
		free(path1);
		print_command_error(command[0][0]);
		handle_command(command[0], NULL, 127);
	}
	if (access(path1, X_OK) == -1)
	{
		free(path1);
		write(2, "pipex: permission denied: ", 26);
		write(2, command[0][0], ft_strlen(command[0][0]));
		write(2, "\n", 1);
		handle_command(command[0], NULL, 126);
	}
	
	execve(path1, command[0], envp);
	free(path1);
	perror("execve failed");
	handle_command(command[0], NULL, EXIT_FAILURE);

}
