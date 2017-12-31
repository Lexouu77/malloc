/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy_no_segfault.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:42:19 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 12:18:25 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*get_max(void *src)
{
	t_block	*block;

	block = get_block(src);
	if (!block)
		return (NULL);
	return ((void*)((char*)block + block->mapped_size));
}

void			*memcpy_no_segfault(void *dest, void *src, size_t n)
{
	size_t		i;
	void		*max;

	max = get_max(src);
	if (!max)
		return (NULL);
	i = 0;
	while (i < n && (void*)((char*)src + i) < max)
	{
		((char*)dest)[i] = ((const char*)src)[i];
		i++;
	}
	return (dest);
}
