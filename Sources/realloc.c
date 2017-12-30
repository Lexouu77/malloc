/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/30 18:33:28 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*unlock_and_leave(void *ptr)
{
	pthread_mutex_unlock(&g_m_mutex);
	return (ptr);
}

static size_t	is_remappable(void *ptr, size_t size)
{
	t_block			*block;
	t_page			*page;

	block = get_block(ptr);
	if (!block->pages)
		return ((block->mapped_size - SZ_BLOCK >= size) ? 1 : 0);
	page = get_page(ptr, block);
	if (page->size >= size)
		return (1);
	if (!page->next || (page->next && !page->next->is_available))
		return (0);
	if (page->next->is_available
		&& page->next->size + page->size >= size)
		return (1);
	return (0);
}

static void		*remap_block(void *ptr, size_t size)
{
	t_block			*block;
	t_page			*page;
	t_page			*tmp;
	size_t			tmp_s;

	block = get_block(ptr);
	page = get_page(ptr, block);
	if (!block->pages || page->size >= size)
		return (unlock_and_leave(ptr));
	if (page->size + page->next->size - size >= SZ_PAGE + 8)
	{
		tmp = page->next->next;
		tmp_s = page->size + page->next->size - size;
		block->used_size = block->used_size - page->size + size;
		page->size = size;
		page->next = (void*)((char*)page + SZ_PAGE + page->size);
		page->next->is_available = 1;
		page->next->size = tmp_s;
		page->next->next = tmp;
		return (unlock_and_leave(ptr));
	}
	page->size += page->next->size;
	block->used_size += page->next->size;
	page->next = page->next->next;
	return (unlock_and_leave(ptr));
}

static size_t	is_same_type(void *ptr, size_t size)
{
	size_t	type;
	t_block	*block;

	if (!(block = get_block(ptr)))
		return (0);
	type = get_map_type(ALIGN(ALIGN_M_64BIT, size));
	if (!block->pages && type == LARGE)
		return (1);
	if (block->mapped_size == (size_t)getpagesize() * SMALL_N_PAGE &&
		type == SMALL)
		return (1);
	if (block->mapped_size == (size_t)getpagesize() * TINY_N_PAGE &&
		type == TINY)
		return (1);
	return (0);
}

void			*realloc(void *ptr, size_t size)
{
	void			*mapped_ptr;

	if (!ptr)
		return (malloc(size));
	pthread_mutex_lock(&g_m_mutex);
	if (!is_mapped(ptr))
	{
		pthread_mutex_unlock(&g_m_mutex);
		return (NULL);
	}
	if (!size)
	{
		pthread_mutex_unlock(&g_m_mutex);
		free(ptr);
		return (NULL);
	}
	if (is_same_type(ptr, size) && is_remappable(ptr, size))
		return (remap_block(ptr, size));
	pthread_mutex_unlock(&g_m_mutex);
	if ((mapped_ptr = malloc(size)))
	{
		memcpy_no_segfault(mapped_ptr, ptr, size);
		free(ptr);
	}
	return (mapped_ptr);
}
