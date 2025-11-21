#include "pipex.h"

void fatal_error(char *msg)
{
    ft_putstr_fd("Error: ",2);
    perror(msg);
    exit(1);
}
void    msg_error(char *msg)
{
    ft_putstr_fd("Error: ",2);
    ft_putendl_fd(msg, 2);
    exit(1);
}
void    free_array(char **arr)
{
    int i;

    if(!arr)
        return;
    i=0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

static char *find_path_var(char **envp)
{
    int i;

    i=0;
    while (envp[i])
    {
        if(ft_strncmp(envp[i], "PATH=",5)==0)
            return (envp[i] + 5);
        i++;
    }
    return NULL;
}

static char *search_and_check(char **all_paths, char *cmd)
{
	char	*path_attempt;
	int		i;

	i = 0;
	while (all_paths[i])
	{
		path_attempt = ft_strjoin_with_slash(all_paths[i], cmd);
		if (!path_attempt)
		{
			free_array(all_paths);
			return (NULL);
		}
		
		if (access(path_attempt, X_OK) == 0)
		{
			free_array(all_paths);
			return (path_attempt);
		}
		
		free(path_attempt);
		i++;
	}
	return (NULL);
}
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	*path_var;
	char	*cmd_path; 
	
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_var = find_path_var(envp);
	if (!path_var)
		return (NULL);
	all_paths = ft_split(path_var, ':');
    if (!all_paths)
        return (NULL);
    cmd_path = search_and_check(all_paths, cmd);
	return (cmd_path);
}
