/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:12:13 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/05 05:37:46 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Recherche la commande a executer et l'execute avec les arguments voulus */

void	ft_start_cmd(t_pipex *data, char **cmd_args)
{
	int		i;
	char	*cmd;

	data->cmd_exists = ((i = -1), 0);
	while (data->paths[++i] && !(data->cmd_exists))
	{
		cmd = ft_strjoin(data->paths[i], cmd_args[0]);
		if (!cmd)
			return ;
		if (!access(cmd, X_OK))
			data->cmd_exists = 1;
		data->path_to_use = i;
		free(cmd);
	}
	if (!data->cmd_exists)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		ft_putendl_fd(cmd_args[0], 2);
		return ;
	}
	cmd = ft_strjoin(data->paths[i - 1], cmd_args[0]);
	if (!cmd)
		return ;
	execve(cmd, &(cmd_args[0]), data->envp);
	free(cmd);
}

/* Lance l'execution de la premiere commande */

void	ft_exec_cmd_one(t_pipex *data)
{
	if (dup2(data->fd_infile, 0) < 0)
	{
		perror("dup2");
		return ;
	}
	if (dup2(data->fd_tube[1], 1) < 0)
	{
		perror("dup2");
		return ;
	}
	close(data->fd_infile);
	close(data->fd_tube[0]);
	ft_start_cmd(data, data->cmd1);
}

/* Lance l'execution de la seconde commande */

void	ft_exec_cmd_two(t_pipex *data)
{
	if (dup2(data->fd_outfile, 1) < 0)
	{
		perror("dup2");
		return ;
	}
	if (dup2(data->fd_tube[0], 0) < 0)
	{
		perror("dup2");
		return ;
	}
	close(data->fd_tube[1]);
	close(data->fd_outfile);
	ft_start_cmd(data, data->cmd2);
}
