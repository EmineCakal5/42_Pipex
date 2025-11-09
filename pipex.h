/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 13:16:23 by ecakal            #+#    #+#             */
/*   Updated: 2025/11/09 15:50:11 by ecakal           ###   ########.fr       */
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