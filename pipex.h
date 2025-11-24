/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcebeci <tcebeci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 01:45:47 by tcebeci           #+#    #+#             */
/*   Updated: 2025/11/25 01:47:44 by tcebeci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

void	fatal_error(char *msg);
void	msg_error(char *msg);
void	free_array(char **arr);
char	*get_cmd_path(char *cmd, char **envp);

#endif