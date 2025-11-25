/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcebeci <tcebeci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:06:15 by tcebeci           #+#    #+#             */
/*   Updated: 2025/11/25 18:22:25 by tcebeci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent_process(pid_t pid1, pid_t pid2, int *pipe_fd)
{
	int	status;

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	execute(char *cmd, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		fatal_error("ft_split");
	if (cmd_args[0] == NULL)
	{
		free_array(cmd_args);
		ft_putstr_fd("Error: command not found\n", 2);
		exit(127);
	}
	cmd_path = get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_array(cmd_args);
		ft_putstr_fd("Error: command not found\n", 2);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
		fatal_error("execve failed");
}

void	child_one(int *pipe_fd, char **argv, char **envp)
{
	int		in_fd;

	in_fd = open(argv[1], O_RDONLY);
	if (in_fd == -1)
		fatal_error(argv[1]);
	dup2(in_fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(in_fd);
	execute(argv[2], envp);
}

void	child_two(int *pipe_fd, char **argv, char **envp)
{
	int		out_fd;

	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		fatal_error(argv[4]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	close(out_fd);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		msg_error("Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(pipe_fd) == -1)
		fatal_error("pipe error");
	pid1 = fork();
	if (pid1 == -1)
		fatal_error("fork1 error");
	if (pid1 == 0)
		child_one(pipe_fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		fatal_error("fork2 error");
	if (pid2 == 0)
		child_two(pipe_fd, argv, envp);
	return (parent_process(pid1, pid2, pipe_fd));
}
