/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:44:42 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/10 17:59:23 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

t_block	*g_m_block = NULL;

size_t			get_map_size(size_t size, size_t type)
{
	if (type == TINY)
		return ((size_t)getpagesize() * TINY_N_PAGE);
	if (type == SMALL)
		return ((size_t)getpagesize() * SMALL_N_PAGE);
	return (ALIGN((size_t)getpagesize(), size + SZ_BLOCK)); // remove SZ_BLOCK if showmemalloc ?
}

void			*queue_block(t_block *new_block, size_t type)
{
	t_block	*ptr;

	if (!g_m_block || (void*)new_block < (void*)g_m_block)
	{
		if ((void*)new_block < (void*)g_m_block)
			new_block->next = g_m_block;
		g_m_block = new_block;
		return ((void*)((char*)new_block + SZ_BLOCK +
					(type == LARGE ? 0 : SZ_PAGE)));
	}
	ptr = g_m_block;
	while (ptr->next)
	{
		if ((void*)new_block > (void*)ptr)
		{
			new_block->next = ptr->next;
			ptr->next = new_block;
			return ((void*)((char*)new_block + SZ_BLOCK +
				(type == LARGE ? 0 : SZ_PAGE)));
		}
		ptr = ptr->next;
	}
	ptr->next = new_block;
	return ((void*)((char*)new_block + SZ_BLOCK +
				(type == LARGE ? 0 : SZ_PAGE)));
}

void			*get_block(void *ptr)
{
	t_block	*block;

	if (!g_m_block)
		return (NULL);
	block = g_m_block;
	while (block->next)
	{
		if (ptr > (void*)block && ptr < (void*)block->next)
			return (block);
		block = block->next;
//		if (!block->next)
//			return (block);
	}
	return (block);
//	return (NULL);
}

void			*insert_page(size_t size, void *ptr)
{
	t_block	*block;
	t_page	*page;
	t_page	*tmp;

	if (!(block = get_block(ptr)))
		return (NULL); // extra safe ?
	page = ptr;
	page->is_available = 0;
	if (SZ_PAGE + 8 <= page->size - size)
	{
		tmp = page->next;
		page->next = (void*)((char*)page + SZ_PAGE + size);
		page->next->next = tmp;
		page->next->size = page->size - size - SZ_PAGE;
		page->next->is_available = 1;
		page->size = size;
		block->used_size += SZ_PAGE + size;
	}
	else
		block->used_size += SZ_PAGE + page->size;
	return ((void*)((char*)page + SZ_PAGE));
}

/*
** Adding SZ_PAGE to used_size when changing to unavailable a page. (if free(block)) and used_size == SZ_BLOCK -> unmap.
*/

void			*create_memory_block(size_t size, size_t type)
{
	const size_t	to_map_size = get_map_size(size, type);
	t_page			*ptr;
	t_block			*new_block;

	if ((new_block = (t_block *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
//	printf("Block = %p, size = %zu\n", (void*)new_block, to_map_size);
	new_block->mapped_size = to_map_size;
	new_block->used_size = (type == LARGE ? size : SZ_BLOCK);
	new_block->pages = NULL;
	new_block->next = NULL;
	if (type == LARGE)
		return (queue_block(new_block, type));
	new_block->used_size += SZ_PAGE + size;
	ptr = (void*)((char*)new_block + SZ_BLOCK);
	ptr->size = size;
	ptr->is_available = 0;
	ptr->next = (void*)((char*)ptr + SZ_PAGE + size);
	ptr->next->size = new_block->mapped_size - new_block->used_size;
	ptr->next->is_available = 1;
	ptr->next->next = NULL;
	new_block->pages = ptr;
	return (queue_block(new_block, type));
}

static void		*check_available_memory(size_t size, size_t type)
{
	t_block	*ptr;
	t_page	*page;

	if (!g_m_block || type == LARGE)
		return (NULL);
	ptr = g_m_block;
	while (ptr)
	{
		page = ptr->pages;
		if (page && (size + SZ_PAGE <= ptr->mapped_size - ptr->used_size ))
		{
			while (page)
			{
				if (page->is_available && page->size >= size)
					return (page);
				page = page->next;
			}
		}
		ptr = ptr->next;
	}
	return (NULL);
}

size_t	get_map_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	if (size <= SMALL_MAX)
		return (SMALL);
	return (LARGE);
}

void			*ft_malloc(size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size);
	const size_t	type = get_map_type(aligned_size);
	void			*ptr;

	if (!size)
		return (NULL);
	if ((ptr = check_available_memory(aligned_size, type)))
		return (insert_page(aligned_size, ptr));
	return (create_memory_block(aligned_size, type));
}


