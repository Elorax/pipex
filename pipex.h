
#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>


typedef struct s_pipex
{
	int	fd_tube[2];
	int	fd_infile;
	int	fd_outfile;
	char	**av;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	pid_t	pid_cm1;
	pid_t	pid_cm2;
	int	status_file1;
	int	status_file2;
	int	status_code;
}	t_pipex;

char	**ft_find_path(char **envp);
int		ft_initialize_pipex(t_pipex *data, char **av, char **env);
void	ft_free_split(char	**s);
void	ft_safe_free(void *ptr);

#endif
