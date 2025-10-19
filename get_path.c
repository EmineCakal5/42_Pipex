#include "unistd.h"
#include "stdio.h"
#include <string.h>
#include "stdlib.h"
#include "fcntl.h"
#include "libft/libft.h"

char *get_path(char *av, char **env)
{
    int i = 0;
    int value = -1;
    char **splitted_path = NULL;
    char *result = NULL;
    char    *tmp = NULL;
    while (env[i] != NULL)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            splitted_path = ft_split(env[i], ':');
            if (!splitted_path)
                return NULL;

            int j = 0;
            while (splitted_path[j])
            {
                tmp = ft_strjoin(splitted_path[j], "/");
                if (!tmp)
                {
                    int k = 0;
                    while (splitted_path[k])
                        free(splitted_path[k++]);
                    free(splitted_path);
                    return NULL;
                }
                result = ft_strjoin(tmp, av);
                free(tmp);
                if(!result)
                {
                    int k = 0;
                    while (splitted_path[k])
                        free(splitted_path[k++]);
                    free(splitted_path);
                    return NULL;
                }
                value = access(result, X_OK);
                if (value == 0)
                {
                    int k = 0;
                    while (splitted_path[k])
                        free(splitted_path[k++]);
                    free(splitted_path);
                    return (result);
                }
                free(result);
                result = NULL;
                j++;
            }
            int k = 0;
            while (splitted_path[k])
                free(splitted_path[k++]);
            free(splitted_path);
            break;  
        }
        i++;
    }
    return (NULL);
}


