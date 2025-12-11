/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:10:40 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 14:24:16 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "fcntl.h"
# include "libft/libft.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include <string.h>
# include <sys/wait.h>

char	*get_path(char *av, char **env);
void	free_split(char **str);
void	clean_pipe(int fd_in, int fd_out, char **command1, char **command2);
void	parent_process(int *pipefd, int fd_out, char **command[], char **envp);
void	child_process(int *pipefd, int fd_in, char **command[], char **envp);
void	dup_and_close(int fd_in, int out);
void	print_command_error(char *cmd);
void	handle_command(char **command1, char **command2, int status);

#endif