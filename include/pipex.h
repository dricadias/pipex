/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:08:34 by adias-do          #+#    #+#             */
/*   Updated: 2025/04/25 22:15:16 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	int		infile;
	int		outfile;
	char	**paths;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
}	t_pipex;

// struct
void	init_struct(t_pipex *node, int argc, char **argv, char **envp);

// childs
void	child_process(t_pipex *node, char **envp);
void	child2_process(t_pipex *node, char **envp);

// utils
char	*get_command_path(char *cmd, char **paths);
char	**get_envp_paths(char **envp);
void	handle_exit(t_pipex *node, pid_t pid1, pid_t pid2);

// errors
void	ft_error(char *msg, int status);
void	free_split(char **array);
void	free_pipex(char *msg, t_pipex *p_struct, int status);

#endif