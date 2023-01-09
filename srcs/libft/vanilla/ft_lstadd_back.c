/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:44:53 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/13 14:44:54 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	while (*lst)
		lst = &((*lst)-> next);
	*lst = new;
}
