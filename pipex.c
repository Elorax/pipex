/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:12:13 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/04 20:32:32 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*Evite des crash en cas de double free*/

void	ft_safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

/* Evite les leaks si le second split ne marche pas. */

void	ft_free_split(char	**s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_safe_free(s[i]);
		i++;
	}
	ft_safe_free(s);
}

/* Recherche la commande a executer et l'execute avec les arguments voulus */

void	ft_start_cmd(t_pipex *data, char **cmd_args)
{
	int		i;
	char	*cmd;

	i = -1;
	data->cmd_exists = 0;
	/* Verification que la commande existe. */
	while (data->paths[++i] && !(data->cmd_exists))
	{
		cmd = ft_strjoin(data->paths[i], cmd_args[0]);
		if (!cmd)
			return ;
		if (!access(cmd, X_OK))	//verfie que la commande existe et est executable
			data->cmd_exists = 1;
		else
			free(cmd);
		data->path_to_use = i;
	}
	/* Si commande non trouvee, le programme ne plante pas mais diffuse un message d'erreur */
	if (!data->cmd_exists)
	{
		ft_putstr_fd("zsh: command not found: ", 2);	
		ft_putstr_fd(cmd_args[0], 2);	
		ft_putstr_fd("\n", 2);	
		return ;
	}

	/* Si commande trouvee, on l'execute */
	if (!cmd)
		return ;//Gerer l'erreur
//	fprintf(stderr, "execve(%s, &cmd_args[0], data->envp);\n", cmd);
	execve(cmd, &(cmd_args[0]), data->envp);	//Ne revient pas si path correct.
//	fprintf(stderr, "execve s'est mal passe\n");
	free(cmd);	//Free si erreur
	exit(EXIT_FAILURE);	//C'est bien ca ?
}

/* Lance l'execution de la premiere commande */

void	ft_exec_cmd_one(t_pipex *data)
{

	if (dup2(data->fd_infile, 0) < 0)	//On remplace stdin par infile pour executer la premiere commande.
	{
		perror("dup2");
		return ;
	}
	if (dup2(data->fd_tube[1], 1) < 0)	//On remplace stdout par tube[1] pour recuperer l'outpur de la premiere commande.
	{
		perror("dup2");
		return ;
	}
	close(data->fd_infile);		//On ferme le fichier infile
	close(data->fd_tube[0]);	//On ferme l'extremite de lecture du tube car on ne l'utilise pas dans ce process.
	ft_start_cmd(data, data->cmd1);
}

/* Lance l'execution de la seconde commande */

void	ft_exec_cmd_two(t_pipex *data)
{
	if (dup2(data->fd_outfile, 1) < 0)	//On remplace stdout par l'outfile pour recuperer l'output de la commande dans outfile.
	{
		perror("dup2");
		return ;
	}
	if (dup2(data->fd_tube[0], 0) < 0)	//On remplace stdin par l'extremite de lecture du tube
	{
		perror("dup2");
		return ;
	}
	//tube[0] est l'extremite de lecture. tube[1] celle d'ecriture
	close(data->fd_tube[1]);	//On ferme l'extremite d'ecriture du tube que l'on n'utilise pas.
	close(data->fd_outfile);	//On ferme le fichier outfile.
	ft_start_cmd(data, data->cmd2);
}

void	ft_pipex(t_pipex *data)
{
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 < 0)
		return(perror("Fork"));
	else if (data->pid_cmd1 == 0)	//On est dans le processus fils.
		ft_exec_cmd_one(data);

	data->pid_cmd2 = fork();
	if (data->pid_cmd2 < 0)
		return(perror("Fork"));
	else if (data->pid_cmd2 == 0 && data->pid_cmd1 != 0)	//On est dans le 2e processus fils.
		ft_exec_cmd_two(data);

	close(data->fd_tube[0]);	//On ferme l'input
	close(data->fd_tube[1]);	//On ferme l'output
	waitpid(data->pid_cmd1, &(data->status_code1), 0);
	waitpid(data->pid_cmd2, &(data->status_code2), 0);
	close(data->fd_infile);
	close(data->fd_outfile);
	exit(EXIT_SUCCESS);
}

/* Initialise la structure pipex */

void	ft_initialize_pipex(t_pipex *data, char **av, char **env)
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
	data->av = av;
	data->envp = env;
	data->paths = ft_find_path(data->envp);
	data->cmd1 = ft_split(av[2], ' ');
	if (!(data->cmd1))
		return ;//Erreur a gerer
	data->cmd2 = ft_split(av[3], ' ');
	if (!(data->cmd2))
		return ;//Erreur a gerer
	ft_pipex(data);
}

int main(int ac, char **av, char **env)
{
	t_pipex	data;
	if (ac != 5)
	{
		ft_putstr_fd("Mauvais nombre d'arguments\n", 2);
		return 0;
	}
	ft_initialize_pipex(&data, av, env);
}
