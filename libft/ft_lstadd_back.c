/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:30:49 by abiersoh          #+#    #+#             */
/*   Updated: 2021/11/22 12:30:55 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cursor;

	if (alst && *alst)
	{
		cursor = *alst;
		while (cursor->next)
			cursor = cursor->next;
		cursor->next = new;
	}
	else if (alst)
		*alst = new;
}
