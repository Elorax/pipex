/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frees.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:12:13 by abiersoh          #+#    #+#             */
/*   Updated: 2021/12/05 04:41:09 by abiersoh         ###   ########.fr       */
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
