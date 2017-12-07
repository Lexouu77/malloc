/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/06 21:00:52 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size);
	const size_t	type = get_map_type(aligned_size);
	
	if (!ptr || !size)
		return (NULL);
	if (is_remappable(ptr, aligned_size, type))
		return (remap_block(ptr, aligned_size, type));
	free(ptr);
	return (malloc(ptr, aligned_size));
}
