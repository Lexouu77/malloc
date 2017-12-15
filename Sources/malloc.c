/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:44:42 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/15 19:59:25 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*g_m_block = NULL;

static void		*queue_block(t_block *new_block, size_t type)
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

static void		*insert_page(size_t size, void *ptr)
{
	t_block	*block;
	t_page	*page;
	t_page	*tmp;

	if (!(block = get_block(ptr)))
		return (NULL);
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

static void		*create_memory_block(size_t size, size_t type)
{
	const size_t	to_map_size = get_map_size(size, type);
	t_page			*ptr;
	t_block			*new_block;

	if ((new_block = (t_block *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
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
		if (page && (size + SZ_PAGE <= ptr->mapped_size - ptr->used_size))
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

void			*malloc(size_t size)
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
