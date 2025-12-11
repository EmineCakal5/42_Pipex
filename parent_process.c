/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:27:41 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 14:28:10 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(int *pipefd, int fd_out, char **command[], char **envp)
{
	char	*path2;

	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(pipefd[0]);
	close(fd_out);
	if (!command[1] || !command[1][0])
	{
		ft_putendl_fd("Error: Second command is empty", STDERR_FILENO);
		handle_command(NULL, command[1], 127);
	}
	path2 = get_path(command[1][0], envp);
	if (path2 == NULL)
	{
		print_command_error(command[1][0]);
		handle_command(NULL, command[1], 127);
	}
	if (access(path2, F_OK) == -1)
	{
		free(path2);
		print_command_error(command[1][0]);
		handle_command(NULL, command[1], 127);
	}
	if (access(path2, X_OK) == -1)
	{
		free(path2);
		write(2, "pipex: permission denied: ", 26);
		write(2, command[1][0], ft_strlen(command[1][0]));
		write(2, "\n", 1);
		handle_command(NULL, command[1], 126);
	}
	
	execve(path2, command[1], envp);
	free(path2);
	perror("execve failed");
	handle_command(NULL, command[1], EXIT_FAILURE);
}
