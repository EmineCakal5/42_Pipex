/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:09:32 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 20:05:17 by ecakal           ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	**command[2];
	int		pipefd[2];
	int		fd_in;
	int		fd_out;

	if (ac != 5)
		return (ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile",
				STDERR_FILENO), 1);
	if (!files_init(av, &fd_in, &fd_out) || !init_commands(av, command))
		return (clean_pipe(fd_in, fd_out, command[0], command[1]), 1);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), clean_pipe(fd_in, fd_out, command[0],
				command[1]), 1);
	if (fork_child(pipefd, fd_in, command, envp) == -1 || fork_parent(pipefd,
			fd_out, command, envp) == -1)
		return (clean_pipe(fd_in, fd_out, command[0], command[1]), 1);
	waitpid(fork_child(pipefd, fd_in, command, envp), NULL, 0);
	waitpid(fork_parent(pipefd, fd_out, command, envp), NULL, 0);
	return (0);
}
