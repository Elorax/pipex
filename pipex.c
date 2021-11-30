#include "pipex.h"


void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	//f1, f2 are two file descriptors.
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork : "));
	if (child1 == 0)
		child_one_process(f1, cmd1);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork : "));
	if (child2 == 0)
		child_two_process(f2, cmd2);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);	//Waiting for childrens to finish tasks
	waitpid(child2, &status, 0);




	parent = fork();
	if (parent < 0)		//Error
		return(perror("Fork: "));
	if (!parent)	//Means we are in the child process
		child_process(f1, cmd1);	//the child writes in the pipe so cmd1 executed by child.
	else			//Means we are in the parent process.
		parent_process(f2, cmd2);	//The parent reads in the pipe so cmd2 executed by parent.

}

static char	*ft_strjoin(char *s1, char *s2);
{
	char	*dest;
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = 0;
	return (dest);
}


void	child_process(int f1, char **av, char **env)
{
	char	**path;

	path = ft_split(env[13], ':');
	cmds = ft_split(av[2], ' ');
	i = -1;
	while(mypaths[++i])
	{
		cmd1 = ft_strjoin(mypaths);

	}
}

int pipex(int f1, int f2, char **av, char **env)
{
	char	**path;
	char	**cmds;
	char	*cmd1;
	int		i;
	int		end[2];
	pid_t	parent;

	parent = fork();
	if (!parent)

	pipe(end);
	path = ft_split(env[13], ':');
	//PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/go/bin:/usr/local/munki
	cmds = ft_split(av[2], ' ');
	i = -1;
	while (mypaths[++i])
	{
		cmd1 = ft_strjoin(my_paths[i], av[2]);
		if (!cmd1)
			return (-42);
		execve(cmd, mycmdargs, env);
		//perror("Error calling execve");
		free(cmd);
	}
	return (EXIT_FAILURE);
}

typedef struct t_
int main(int ac, char **av, char **env)
{
	int		fd1;
	int		fd2;

	if (ac != 5)
	{
		printf("Mauvais nombre d'arguments\n");
		return 0;
	}
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
