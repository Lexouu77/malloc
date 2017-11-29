/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/11/29 22:39:37 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_m_zone	*m_zone = NULL;

static size_t	get_map_size(size_t size, size_t type)
{
	if (type == TINY)
		return (getpagesize() * TINY_N_PAGE);
	if (type == SMALL)
		return (getpagesize() * SMALL_N_PAGE);
	return (ALIGN(ALIGN_GETPAGESIZE, size));
}

void			*create_memory_block(size_t size, size_t type)
{
	const size_t	to_map_size = get_map_size(size, type);

	if ((m_zone = (t_m_zone *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	 return (NULL);
	m_zone->mapped_size = to_map_size;
	m_zone->used_size = SZ_BLOCK;
	m_zone->pages = NULL;
	m_zone->next = NULL;
	if (type == LARGE)
		return ((void*)&m_zone + SZ_BLOCK);
	prefill_pages(type); // TODO ADD Address value ?
	resize_page(size); // resize le size de la premiere page et change la valeur de son next a page->next + 8 + size
	return ((void*)&m_zone + SZ_BLOCK + SZ_PAGE);
}

size_t			check_available_memory(size_t size, size_t type)
{
	t_m_zone	*ptr;
	size_t		i;

	if (!m_zone)
		return (0);
	if (type == LARGE)
		return (1);
	ptr = m_zone;
	i = 1;
	while (ptr)
	{
		if (((ptr->mapped_size == (getpagesize() * TINY_N_PAGE) && type == TINY)
			|| (ptr->mapped_size == (getpagesize() * SMALL_N_PAGE) &&
				type == SMALL)) &&
			(size <= (ptr->mapped_size - (ptr->used_size + SZ_PAGE))))
			return (i);
		i++;
		ptr = ptr->next;
	}
	return (0);
}

static size_t	get_map_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	if (size <= SMALL_MAX)
		return (SMALL);
	return (LARGE);
}

void			*malloc(size_t size)
{
	size_t	type;
	size_t	n;

	if (!size)
		return (NULL);
	n = 0;
	type = get_map_type(size);
	if ((n = check_available_memory(size, type)))
		return (send_memory_pointer(size, type, n)); // TODO queue it in send_memory_pointer if type == LARGE create a new and queue. TODO change name, maybe do a queue function and create?/ another or w/e
	return (create_memory_block(size, type));
}
