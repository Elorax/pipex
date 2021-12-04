/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:57:12 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/04 16:41:57 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "pipex.h"

char	**ft_find_path(char **envp)
{
	char	**str;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	if (envp[i] != NULL)
		str = ft_split(ft_strchr(envp[i], '/'), ':');
	else
		str = NULL;
	if (str)
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_strjoin(str[i], "/");	//Leaks ici
			i++;
		}
	}
	return str;
}

/*int main(int ac, char **av, char **envp)
{
	char	**str;
	int		i;

	(void) ac;
	(void) av;
	i = 0;
	str = ft_find_path(envp);
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}

	free(str);
}*/
