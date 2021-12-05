/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:57:12 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/05 02:55:00 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */





#include "pipex.h"

char	*ft_slash(char *s1)
{
	char	*dest;
	int		size;

	size = ft_strlen(s1) + 2;
	dest = malloc(size);
	if (!dest)
		return (NULL);//free_split
	ft_strlcpy(dest, s1, size - 1);
	free(s1);
	ft_strlcat(dest, "/", size);
	return (dest);
}

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
			str[i] = ft_slash(str[i]);	//probably leaks here
			i++;
		}
	}
	return str;
}


/*
int main(int ac, char **av, char **env)
{
	int	i = 0;
	char **str = ft_find_path(env);
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}*/
