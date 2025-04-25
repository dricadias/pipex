/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adias-do <adias-do@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:01:15 by adias-do          #+#    #+#             */
/*   Updated: 2025/04/25 20:37:16 by adias-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_error(char *msg, int status)
{
	if (msg)
		ft_putendl_fd(msg, status);
	exit(status);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_pipex(char *msg, t_pipex *p_struct, int status)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	if (p_struct->infile > 0)
		close(p_struct->infile);
	if (p_struct->outfile > 0)
		close(p_struct->outfile);
	if (p_struct->paths)
		free_split(p_struct->paths);
	if (p_struct->cmd1_args)
		free_split(p_struct->cmd1_args);
	if (p_struct->cmd2_args)
		free_split(p_struct->cmd2_args);
	if (p_struct->cmd1_path)
		free(p_struct->cmd1_path);
	if (p_struct->cmd2_path)
		free(p_struct->cmd2_path);
	free(p_struct);
	exit(status);
}
