#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"

#include <stdio.h> //perror için
#include <unistd.h> //access,dup2,execve,fork,pipe,close
#include <fcntl.h> //open,0_... ++ için
#include <stdlib.h> //exit
#include <sys/wait.h> //wait,waitpid


void    fatal_error(char *msg);
void    msg_error(char *msg);
void    free_array(char **arr);
char    *get_cmd_path(char *cmd, char **envp);

#endif