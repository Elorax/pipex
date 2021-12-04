#include "pipex.h"

/*Evite des crash en cas de double free*/

void	ft_safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

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
			//Gerer l'erreur
		fprintf(stderr, "test du chemin -->%s<--\n", cmd);
		if (!access(cmd, X_OK))		//verfie que la commande existe et est executable
			data->cmd_exists = 1;
			data->path_to_use = i;
		free(cmd);
	}
	/* Si commande non trouvee, le programme ne plante pas mais diffuse un message d'erreur */
	if (!data->cmd_exists)
	{
		fprintf(stderr, "\n\n-bash: %s: command not found\n", cmd_args[0]);	//A virer
		return ;
	}

	/* Si commande trouvee, on l'execute */
	cmd = ft_strjoin(data->paths[data->path_to_use], cmd_args[0]);
	if (!cmd)
		return ;//Gerer l'erreur
	fprintf(stderr, "execve(%s, &cmd_args[0], data->envp);\n", cmd);
	execve(cmd, &(cmd_args[0]), data->envp);	//Ne revient pas si path correct.
	fprintf(stderr, "execve s'est mal passe\n");
	free(cmd);	//Free si erreur
	//Gestion d'erreur a faire (exit ?)
}


void	ft_exec_cmd_one(t_pipex *data)
{

	if (dup2(data->fd_infile, 0) < 0)	//On remplace stdin par infile pour executer la premiere commande.
	{
		//Gerer l'erreur
		close(0);
		exit(EXIT_FAILURE);
	}
	dup2(data->fd_tube[1], 1);	//On remplace stdout par tube[1] pour recuperer l'outpur de la premiere commande.
	close(data->fd_infile);		//On ferme le fichier infile
	close(data->fd_tube[0]);	//On ferme l'extremite de lecture du tube car on ne l'utilise pas dans ce process.
	ft_start_cmd(data, data->cmd1);
}

void	ft_exec_cmd_two(t_pipex *data)
{
	dup2(data->fd_outfile, 1);	//On remplace stdout par l'outfile pour recuperer l'output de la commande dans outfile.
	dup2(data->fd_tube[0], 0);	//On remplace stdin par l'extremite de lecture du tube
	//tube[0] est l'extremite de lecture. tube[1] celle d'ecriture
	close(data->fd_tube[1]);	//On ferme l'extremite d'ecriture du tube que l'on n'utilise pas.
	close(data->fd_outfile);	//On ferme le fichier outfile.
	int	i = -1;
	fprintf(stderr, "Exectution de la comande deux avec cmd2 = :\n");
	while (data->cmd2[++i])
		fprintf(stderr, "%s\n", data->cmd2[i]);
	ft_start_cmd(data, data->cmd2);
}

void	ft_initialize_pipex(t_pipex *data, char **av, char **env)
{
	pipe(data->fd_tube);
	data->cmd_exists = 0;
	data->path_to_use = 0;
	data->status_code1 = 0;
	data->status_code2 = 0;
	fprintf(stderr, "test\n");

	/* Verification des acces aux fichiers */
	data->fd_infile = open(av[1], O_RDONLY);
	if (data->fd_infile < 0)
		return (perror("open : "));
//	if (access(av[1], F_OK) == -1)
//		return (perror("access : "));
	data->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile < 0)
		return (perror("open : "));
//	if (access(av[4], F_OK) == -1)
//		return (perror("access : "));

	/* Sauvegarde de av et env, initialisation des char **cmd */
	data->av = av;
	data->envp = env;
	data->paths = ft_find_path(data->envp);
	data->cmd1 = ft_split(av[2], ' ');
	if (!(data->cmd1))
		return ;//Erreur a gerer
	data->cmd2 = ft_split(av[3], ' ');
	if (!(data->cmd2))
		return ;//Erreur a gerer

	/* Duplication du programme */
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 < 0)
		return(perror("Fork : "));
	else if (data->pid_cmd1 == 0)	//On est dans le processus fils.
		ft_exec_cmd_one(data);

	/* Duplication du programme again */
	//waitpid ?
	data->pid_cmd2 = fork();
	if (data->pid_cmd2 < 0)
		return(perror("Fork : "));
	if (data->pid_cmd2 == 0 && data->pid_cmd1 != 0)	//On est dans le 2e processus fils.
		ft_exec_cmd_two(data);

	/* Jusque la je gere */
	close(data->fd_tube[0]);	//On ferme l'input
	close(data->fd_tube[1]);	//On ferme l'output
	waitpid(data->pid_cmd1, &(data->status_code1), 0);	//parentheses ?
	waitpid(data->pid_cmd2, &(data->status_code2), 0);	//parentheses ?
	close(data->fd_infile);
	close(data->fd_outfile);
}

int main(int ac, char **av, char **env)
{
	t_pipex	data;
	if (ac != 5)
	{
		printf("Mauvais nombre d'arguments\n");
		return 0;
	}
	ft_initialize_pipex(&data, av, env);
}
