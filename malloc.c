/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/06 20:48:11 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*g_m_block = NULL;

size_t			get_map_size(size_t size, size_t type)
{
	if (type == TINY)
		return ((size_t)getpagesize() * TINY_N_PAGE);
	if (type == SMALL)
		return ((size_t)getpagesize() * SMALL_N_PAGE);
	return (ALIGN(ALIGN_GETPAGESIZE, size));
}

void			*queue_block(t_block *new_block, size_t type)
{
	t_block	*ptr;

	if (!g_m_block)
	{
		g_m_block = new_block;
		return ((void*)((char*)g_m_block + SZ_BLOCK +
					(type == LARGE ? 0 : SZ_PAGE)));
	}
	ptr = g_m_block;
	while (ptr->next)
	{
		if ((void*)new_block > (void*)ptr && (void*)new_block <
				(void*)ptr->next)
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

void			*create_memory_block(size_t size, size_t type)
{
	const size_t	to_map_size = get_map_size(size, type);
	t_page			*ptr;
	t_block		*new_block;

	if ((new_block = (t_block *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->mapped_size = to_map_size;
	new_block->used_size = (type == LARGE ? to_map_size : SZ_BLOCK);
	new_block->pages = NULL;
	new_block->next = NULL;
	if (type == LARGE)
		return (queue_block(new_block, type));
	new_block->used_size += SZ_PAGE + size;
	ptr = (void*)((char*)new_block + SZ_BLOCK);
	ptr->size = SZ_PAGE + size;
	ptr->is_available = 0;
	ptr->next = (void*)((char*)ptr + SZ_PAGE + size);
	ptr->next->size = new_block->mapped_size - new_block->used_size - SZ_PAGE;
	ptr->next->is_available = 1;
	ptr->next->next = NULL;
	new_block->pages = ptr;
	return (queue_block(new_block, type));
}

static void		*check_available_memory(size_t size, size_t type) // TODO CHANGE IT. return 2 int ? n block n page ? return POINTER ?
{
	t_block	*ptr;
	t_page	*page;

	if (!g_m_block || type == LARGE)
		return (NULL);
	ptr = g_m_block;
	while (ptr)
	{
		page = ptr->pages;
		if (page && (size <= (ptr->mapped_size - (ptr->used_size + SZ_PAGE))))
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

void			*insert_page(size_t size, void *ptr)
{
	t_block	*block;
	t_page	*page;

	block = g_m_block;
	while (block)
	{
		if (!block->next)
			break ;
		if (ptr > (void*)block && ptr < (void*)block->next) // >= ? no.
			break ;
		block = block->next;
	}
	page = ptr;
	block->used_size += SZ_PAGE + size;
	page->next = (void*)((char*)page + SZ_PAGE + size);
	page->is_available = 0;
	page->next->size = block->mapped_size - block->used_size - SZ_PAGE;
	page->next->is_available = 1;
	page->next->next = NULL;
	return ((void*)((char*)page + SZ_PAGE));
}

size_t			get_map_type(size_t size)
{
	if (size <= TINY_MAX)
		return (TINY);
	if (size <= SMALL_MAX)
		return (SMALL);
	return (LARGE);
}

void			*malloc(size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size);
	const size_t	type = get_map_type(aligned_size);
	void			*ptr;

	if (!size)
		return (NULL);
	ptr = 0;
//	type = get_map_type(aligned_size);
	if ((ptr = check_available_memory(aligned_size, type)))
		return (insert_page(aligned_size, ptr)); // TODO queue it in send_memory_pointer if type == LARGE create a new and queue. TODO change name, maybe do a queue function and create?/ another or w/e
	// TODO IF cant resize or break pages, call check_available_memory from block->n*next etc, if not possible  just do a new one.
	return (create_memory_block(aligned_size, type));
}
// lock
// void *newptr;
// if ((ptr = check_available_memory(aligned_size, type)))
//		 newptr =  (insert_page(aligned_size, ptr));
//	else
//		 newptr = create_memory_block(aligned_size, type));
//	unlock
//	return (newptr);

