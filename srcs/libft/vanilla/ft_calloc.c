/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nghulam- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:12:17 by nghulam-          #+#    #+#             */
/*   Updated: 2022/05/09 12:12:19 by nghulam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vanilla.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	size_t		i;

	if (!size || !nmemb)
		return (malloc(0));
	if (nmemb * size / size != nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (ptr);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
