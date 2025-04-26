/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:08:08 by adias-do          #+#    #+#             */
/*   Updated: 2025/04/26 05:22:56 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(t_pipex *node, char **envp)
{
	if (!node->cmd1_path)
	{
		ft_putstr_fd(node->cmd1_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free_pipex(NULL, node, 127);
	}
	dup2(node->infile, STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	close(node->fd[0]);
	close(node->fd[1]);
	close(node->infile);
	close(node->outfile);
	if (execve(node->cmd1_path, node->cmd1_args, envp) == -1)
	{
		perror(node->cmd1_path);
		free_pipex(NULL, node, 1);
	}
}

void	child2_process(t_pipex *node, char **envp)
{
	if (!node->cmd2_path)
	{
		ft_putstr_fd(node->cmd2_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free_pipex(NULL, node, 127);
	}
	if (node->outfile < 0)
	{
		perror("outfile");
		free_pipex(NULL, node, 1);
	}
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->outfile, STDOUT_FILENO);
	close(node->fd[0]);
	close(node->fd[1]);
	close(node->infile);
	close(node->outfile);
	if (execve(node->cmd2_path, node->cmd2_args, envp) == -1)
	{
		perror(node->cmd2_path);
		free_pipex(NULL, node, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	t_pipex	*node;

	node = malloc(sizeof(t_pipex));
	if (!node)
		ft_error("malloc failed", 1);
	ft_memset(node, 0, sizeof(t_pipex));
	init_struct(node, argc, argv, envp);
	if (pipe(node->fd) == -1)
		free_pipex("pipe failed", node, 1);
	pid1 = fork();
	if (pid1 == -1)
		free_pipex("fork failed", node, 1);
	if (pid1 == 0)
		child_process(node, envp);
	pid2 = fork();
	if (pid2 == -1)
		free_pipex("fork failed", node, 1);
	if (pid2 == 0)
		child2_process(node, envp);
	close(node->fd[0]);
	close(node->fd[1]);
	handle_exit(node, pid1, pid2);
	return (0);
}
