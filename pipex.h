/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:10:40 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/06 02:10:43 by ecakal           ###   ########.fr       */
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

#endif