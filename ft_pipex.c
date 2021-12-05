/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:12:13 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/05 08:19:56 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Duplique le processus,				*/
/* Execute les deux commandes,			*/
/* Attend la fin de leur execution,		*/
/* Et libere toute la memoire allouee.	*/

void	ft_pipex(t_pipex *data)
{
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 < 0)
		return (perror ("Fork"));
	else if (data->pid_cmd1 == 0)
		ft_exec_cmd_one(data);
	data->pid_cmd2 = fork();
	if (data->pid_cmd2 < 0)
		return (perror ("Fork"));
	else if (data->pid_cmd2 == 0 && data->pid_cmd1 != 0)
		ft_exec_cmd_two(data);
	close(data->fd_tube[0]);
	close(data->fd_tube[1]);
	waitpid(data->pid_cmd1, &(data->status_code1), 0);
	waitpid(data->pid_cmd2, &(data->status_code2), 0);
	close(data->fd_infile);
	close(data->fd_outfile);
	ft_free_split(data->cmd1);
	ft_free_split(data->cmd2);
	ft_free_split(data->paths);
	exit(EXIT_SUCCESS);
}

/* Initialise la structure pipex */

void	ft_init_part_one(t_pipex *data, char **av)
{
	pipe(data->fd_tube);
	data->cmd_exists = 0;
	data->path_to_use = 0;
	data->status_code1 = 0;
	data->status_code2 = 0;
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile < 0)
		perror("open");
	data->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile < 0)
		perror("open");
	if (access(av[1], R_OK) == -1 || access(av[4], W_OK == -1))
		perror("access");
}

/* Initialise la structure pipex */

void	ft_initialize_pipex(t_pipex *data, char **av, char **env)
{
	ft_init_part_one(data, av);
	data->av = av;
	data->envp = env;
	data->paths = ft_find_path(data->envp);
	data->cmd1 = ft_split(av[2], ' ');
	if (!(data->cmd1))
	{
		ft_free_split(data->paths);
		return ;
	}
	data->cmd2 = ft_split(av[3], ' ');
	if (!(data->cmd2))
	{
		ft_free_split(data->paths);
		ft_free_split(data->cmd1);
		return ;
	}
	ft_pipex(data);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	data;

	if (ac != 5)
	{
		ft_putstr_fd("Mauvais nombre d'arguments\n", 2);
		return (0);
	}
	ft_initialize_pipex(&data, av, env);
}
