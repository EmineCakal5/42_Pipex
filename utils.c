/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:23:14 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/06 20:34:36 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup_and_close(int fd_in, int out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(fd_in);
	close(out);
}

void	print_command_error(char *cmd)
{
	ft_putstr_fd("pipex: command not found: ", STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
}

void	handle_command(char **command1, char **command2, int status)
{
	if (command1)
		free_split(command1);
	if (command2)
		free_split(command2);
	exit(status);
}
