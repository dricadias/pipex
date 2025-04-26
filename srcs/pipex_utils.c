/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:27:38 by adias-do          #+#    #+#             */
/*   Updated: 2025/04/26 14:21:29 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_struct(t_pipex *node, int argc, char **argv, char **envp)
{
	if (argc != 5)
		free_pipex("invalid number of args", node, 1);
	node->infile = open(argv[1], O_RDONLY);
	if (node->infile < 0)
	{
		perror(argv[1]);
		node->infile = open("/dev/null", O_RDONLY);
		if (node->infile < 0)
			free_pipex("failed to open /dev/null", node, 1);
	}
	node->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->outfile < 0)
		perror(argv[4]);
	node->paths = get_envp_paths(envp);
	node->cmd1_args = ft_split(argv[2], ' ');
	if (!node->cmd1_args || !node->cmd1_args[0])
		free_pipex("command not found: ''", node, 127);
	node->cmd2_args = ft_split(argv[3], ' ');
	if (!node->cmd2_args || !node->cmd2_args[0])
		free_pipex("command not found: ''", node, 127);
	node->cmd1_path = get_command_path(node->cmd1_args[0], node->paths);
	node->cmd2_path = get_command_path(node->cmd2_args[0], node->paths);
}

char	*get_command_path(char *cmd, char **paths)
{
	int		i;
	char	*tmp;
	char	*full_path;

	if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	tmp = NULL;
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	**get_envp_paths(char **envp)
{
	char	**paths;
	char	*path_var;

	path_var = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path_var = *envp + 5;
			break ;
		}
		envp++;
	}
	if (!path_var)
		ft_error("PATH not found in environment variables", EXIT_FAILURE);
	paths = ft_split(path_var, ':');
	if (!paths)
		ft_error("failed to split PATH", EXIT_FAILURE);
	return (paths);
}

void	handle_exit(t_pipex *node, pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;

	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	if (WIFEXITED(status2))
		free_pipex(NULL, node, WEXITSTATUS(status2));
	else
		free_pipex(NULL, node, 1);
}
