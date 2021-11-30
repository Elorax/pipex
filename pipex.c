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




int main(int ac, char **av, char **env)
{
	if (ac != 5)
	{
		printf("Mauvais nombre d'arguments\n");
		return 0;
	/
	
	char	**cmd1 = ft_split(av[2], ' ');
	char	**cmd2 = ft_split(av[3], ' ');
	int	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		return(perror("Open : "));
	int fd2 = open(argv[4], O_WRONLY);
	if (fd2 == -1)
		return(perror("Open : "));
	char	*path = envp[8];




}
