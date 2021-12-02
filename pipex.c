#include "pipex.h"

/*Evite des crash en cas de double free*/

void	ft_safe_free(void *ptr)
{
	free(*ptr);
	ptr = NULL;
}

void	ft_free_split(char	**s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_safe_free(s[i])
		i++;
	}
	ft_safe_free(s);
}


void	ft_start_cmd(t_pipex *data, char **cmd)
{
	data->input_temp_cmd = cmd[0];
	if (access(cmd[0], F_OK) == 0 && f

}


void	ft_exec_cmd_one(t_pipex *data)
{

	if (dup2(data->fd_infile, 0) < 0)
	{
		//Gerer l'erreur
		close(0);
		exit(EXIT_FAILURE);
	}
	dup2(data->fd_tube[1], 1);	//On remplace stdout par l'extremite d'ecriture du tube
	close(data->fd_infile);		//On ferme le fichier infile
	close(data->fd_tube[0]);	//On ferme l'extremite de lecture du tube.
	ft_start_cmd(data, data->cmd1);
}

void	ft_exex_cmd_two(t_pipex *data)
{
	dup2(data->fd_outfile, 1);	//dup2 de fd outfil et stdout
	dup2(data->fd_tube[0], 0);	//dup2 de tube[0] et stdin
	//tube[0] est l'extremite de lecture. tube[1] celle d'ecriture.
	close(data->fd_tube[1]);
	close(data->fd_outfile);
	ft_start_cmd(data, input->cmd2);
}

int	ft_initialize_pipex(t_pipex *data, char **av, char **env)
{
	
	pipe(data->fd_tube);	//compran pa vremans
	data->status_file1 = 0;
	data->status_code = 0;

	data->fd_infile = open(av[1], O_RDONLY);
	if (access(av[1], F_OK) == -1)		//maybe R_OK
		return (-1);
	data->fd_outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC 0644);
	if (access(av[4], F_OK) == -1)		//maybe W_OK
		return (-1);
	data->av = av;
	data->envp = env;
	data->cmd1 = ft_split(av[2], ' ');
	if (!(data->cmd1))
		return (-1);
	data->cmd2 = ft_split(av[3], ' ');
	if (!(data->cmd2))
	{
		ft_free_split(data->cmd1);
		return (NULL);
	}
	data->pid_cmd1 = fork();
	if (data->pid_cmd1 < 0)
		return(perror("Fork : "));
	if (pid_cmd1 == 0)
		ft_exec_cmd_one(data);
	data->pid_cmd2 = fork();
	if (data->pid_cmd2 < 0)
		return(perror("Fork : "));
	if (data->pid_cmd2 == 0)
		ft_exec_cmd_two(data);
	close(data->fd_tube[0]);	//On ferme l'input
	close(data->fd_tube[1]);	//On ferme l'output
	waitpid(data->pid_cmd1, &(data->status_code), 0);	//parentheses ?
	waitpid(data->pid_cmd2, &(data->status_code), 0);	//parentheses ?
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



	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		return(perror("Open : "));
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 == -1)
		return(perror("Open : "));
	pipex(f1, f2, ag, envp);
	close(f1);
	close(f2);
}
