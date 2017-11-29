/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/11/29 18:34:24 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_m_zone	*m_zone = NULL;



static size_t	get_map_type(size_t size)
{
	if (size <= TINY_MAX)
		return (1);
	if (size <= SMALL_MAX)
		return (2);
	return (3);
}

void			*malloc(size_t size)
{
	const size_t	type = get_map_type(size);

	if (!size)
		return (NULL);
	if (check_available_memory())
		return (send_memory_pointer()); // TODO queue it in send_memory_pointer
	return (create_memory_block(size));
}
