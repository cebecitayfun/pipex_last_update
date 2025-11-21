#include "pipex.h"

void child_one(int *pipe_fd, char **argv, char **envp)
{
    int     in_fd;
    char    **cmd_args;
    char    *cmd_path;

    in_fd=open(argv[1], O_RDONLY);
    if(in_fd == -1)
        fatal_error(argv[1]);
    dup2(in_fd,0);
    dup2(pipe_fd[1],1);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(in_fd);
    cmd_args = ft_split(argv[2], ' ');
    if (!cmd_args)
        msg_error("ft_split failed");
    cmd_path = get_cmd_path(cmd_args[0], envp);
    if(!cmd_path)
    {
        free_array(cmd_args);
        msg_error("command not found");
    }
    if(execve(cmd_path, cmd_args, envp) == -1)
        fatal_error("execve child1 failed");
}
void    child_two(int *pipe_fd, char **argv, char **envp)
{
    int     out_fd;
    char    **cmd_args;
    char    *cmd_path;

    out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(out_fd == -1)
        fatal_error(argv[4]);
    dup2(pipe_fd[0],0);
    dup2(out_fd,1);
    close(pipe_fd[1]);
    close(pipe_fd[0]);
    close(out_fd);
    cmd_args = ft_split(argv[3], ' ');
    if (!cmd_args)
        msg_error("ft_split failed");
    cmd_path = get_cmd_path(cmd_args[0], envp);
    if(!cmd_path)
    {
        free_array(cmd_args);
        msg_error("command not found");
    }
    if (execve(cmd_path, cmd_args, envp) == -1)
        fatal_error("execve child2 failed");
}
int main(int argc, char **argv, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid1;
    pid_t   pid2;

    if (argc != 5)
        msg_error("usage ./pipex file1 cmd1 cmd2 file2");
    if (pipe(pipe_fd) == -1)
        fatal_error("pipe");
    pid1=fork();
    if(pid1 == -1)
        fatal_error("fork1 error");
    if(pid1 == 0)
        child_one(pipe_fd,argv,envp);
    pid2 = fork();
    if (pid2== -1)
        fatal_error("fork2 error");
    if (pid2 == 0)
        child_two(pipe_fd,argv,envp);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

