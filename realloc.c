/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/07 20:27:14 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	is_mapped(void *ptr)
{

	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size);
	const size_t	type = get_map_type(aligned_size);
	
	if (!ptr || !size)
		return (NULL);

	if (is_remappable(ptr, aligned_size, type))
		return (remap_block(ptr, aligned_size, type));
	free(ptr);
	return (malloc(aligned_size));
}
