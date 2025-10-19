#include "fcntl.h"
#include "stdio.h"
#include "sys/wait.h"
#include "unistd.h"
#include "stdlib.h"
#include "libft/libft.h"

char    *get_path(char *av, char **env);

int main(int ac, char **av, char **envp)
{
    if (ac != 5)
        return (0);
    
    char    *path1;
    char    **command1;
    char    *path2;
    char    **command2;
    int pid;
    int pipefd[2];
    int    fd_in;
    int    fd_out;

    fd_in = open(av[1], O_RDONLY , 0644);
    if (fd_in == -1)
    {
        perror("Error opening input file.");
        return 1;
    }

    fd_out = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd_out == -1)
    {
        perror("Error opening output file.");
        return 1;
    }

    command1 = ft_split(av[2], ' ');
    if (!command1)
        exit(EXIT_FAILURE);
    path1 = get_path(command1[0], envp);
    if (path1 == NULL)
    {
        perror("First command is invalid");
        exit(EXIT_FAILURE);
    }

    command2 = ft_split(av[3], ' ');
    if (!command2)
        exit(EXIT_FAILURE);
    path2 = get_path(command2[0], envp);
    if (path2 == NULL)
    {
        perror("Second command is invalid");
        exit(EXIT_FAILURE);
    }
    
    if (pipe(pipefd) == -1)
    {
        perror("Error creating pipe!");
        close(fd_in);
        close(fd_out);
        return 1;
    }
    pid = fork();

    if (pid == 0)
    {
        dup2(fd_in , STDIN_FILENO);
        dup2(pipefd[1] , STDOUT_FILENO);
        close(pipefd[0]);
        execve(path1, command1, envp);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        dup2(fd_out, STDOUT_FILENO);
        close(pipefd[1]);
        execve(path2, command2, envp);
        perror("execve failed");
        exit(EXIT_FAILURE);

    }
    else if (pid == -1)
    {
        perror("Error fork");
        close(fd_in);
        close(fd_out);
        close(pipefd[0]);
        close(pipefd[1]);
        return 1;

    }
        wait(NULL);
}