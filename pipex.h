/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 08:20:15 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/05 08:20:34 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		fd_tube[2];
	int		fd_infile;
	int		fd_outfile;
	char	**av;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	pid_t	pid_cmd1;
	pid_t	pid_cmd2;
	int		status_file1;
	int		status_file2;
	int		status_code1;
	int		status_code2;
	int		cmd_exists;
	int		path_to_use;
}	t_pipex;

char	*ft_slash(char *s1);
void	ft_pipex(t_pipex *data);
void	ft_start_cmd(t_pipex *data, char **cmd_args);
void	ft_exec_cmd_one(t_pipex *data);
void	ft_exec_cmd_two(t_pipex *data);
char	**ft_find_path(char **envp);
void	ft_init_part_one(t_pipex *data, char **av);
void	ft_initialize_pipex(t_pipex *data, char **av, char **env);
void	ft_free_split(char	**s);
void	ft_safe_free(void *ptr);

#endif
