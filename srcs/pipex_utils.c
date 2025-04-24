/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:27:38 by adias-do          #+#    #+#             */
/*   Updated: 2025/04/24 20:35:01 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_struct(t_pipex *node, char **argv, char **envp)
{
	node->infile = open(argv[1], O_RDONLY);
	if (node->infile < 0)
		free_pipex("failed to open infile", node, 1);
	node->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (node->outfile < 0)
		free_pipex("failed to open outfile", node, 1);
	node->paths = get_envp_paths(envp);
	node->cmd1_args = ft_split(argv[2], ' ');
	node->cmd2_args = ft_split(argv[3], ' ');
	node->cmd1_path = get_command_path(node->cmd1_args[0], envp);
	node->cmd2_path = get_command_path(node->cmd2_args[0], envp);
}
