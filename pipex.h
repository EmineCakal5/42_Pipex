/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 18:12:56 by ecakal            #+#    #+#             */
/*   Updated: 2025/07/13 23:59:22 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "unistd.h"
#include "stdio.h"
#include <string.h>
#include "stdlib.h"
#include "fcntl.h"
#include "libft/libft.h"

char *get_path(char *av, char **env);

#endif