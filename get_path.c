/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakal <ecakal@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:10:58 by ecakal            #+#    #+#             */
/*   Updated: 2025/12/11 14:17:29 by ecakal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **str)
{
	int	k;

	k = 0;
	if (!str)
		return ;
	while (str[k])
		free(str[k++]);
	free(str);
}

static char	*get_command_path(char **paths, char *av)
{
	int		j;
	char	*tmp;
	char	*result;

	tmp = NULL;
	result = NULL;
	j = 0;
	while (paths[j])
	{
		tmp = ft_strjoin(paths[j], "/");
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, av);
		free(tmp);
		if (!result)
			return (NULL);
		if (access(result, X_OK) == 0)
			return (result);
		free(result);
		j++;
	}
	return (NULL);
}

char	*get_path(char *av, char **env)
{
	int		i;
	char	*result;
	char	**splitted_path;

	splitted_path = NULL;
	if (!av || !av[0])
		return (NULL);
	if (ft_strchr(av, '/'))
		return (ft_strdup(av));
	i = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			splitted_path = ft_split(env[i] + 5, ':');
			if (!splitted_path)
				return (NULL);
			result = get_command_path(splitted_path, av);
			free_split(splitted_path);
			return (result);
		}
		i++;
	}
	return (NULL);
}
