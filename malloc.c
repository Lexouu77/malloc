/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/03 18:15:59 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block	*g_m_block = NULL;

static size_t	get_map_size(size_t size, size_t type)
{
	if (type == TINY)
		return ((size_t)getpagesize() * TINY_N_PAGE);
	if (type == SMALL)
		return ((size_t)getpagesize() * SMALL_N_PAGE);
	return (ALIGN(ALIGN_GETPAGESIZE, size));
}

static void		prefill_pages(t_page *page, size_t type)
{
	size_t		i;
	t_page		*ptr;

	i = 0;
	ptr = page;
	while (i < N_MIN_ALLOC)
	{
		ptr->size = (type == TINY ? TINY_MAX : SMALL_MAX);
		ptr->is_available = 1;
		ptr->next = (void*)((char*)ptr + SZ_PAGE +
			(type == TINY ? TINY_MAX : SMALL_MAX));
		ptr = ptr->next;
		i++;
	}
	ptr->next = NULL;
}

// TODO ALIGN A 8 LA SIZE DANS create_memory_block

static void		*queue_block(t_block *new_block, size_t type)
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
		ptr = ptr->next;
	ptr->next = new_block;
	return ((void*)((char*)new_block + SZ_BLOCK +
				(type == LARGE ? 0 : SZ_PAGE)));
}

static void		resize_page(t_page *page, size_t size)
{
	

}

static void		*create_memory_block(size_t size, size_t type)
{
	const size_t	to_map_size = get_map_size(size, type);
	t_page			*ptr;
	t_page			*tmp;
	t_block		*new_block;

	if ((new_block = (t_block *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_block->mapped_size = to_map_size;
	new_block->used_size = SZ_BLOCK;
	new_block->pages = NULL;
	new_block->next = NULL;
	if (type == LARGE)
		return (queue_block(new_block, type));
	ptr = (void*)((char*)new_block + SZ_BLOCK);
	prefill_pages(ptr, type);
	new_block->pages = ptr;
	resize_page(ptr, size);
	return (queue_block(new_block, type));

/*
	g_m_block->pages = (void*)((char*)g_m_block + SZ_BLOCK);
//	prefill_pages(type); // TODO ADD Address value as arg ?
	ptr = g_m_block->pages;
	tmp = g_m_block->pages->next;
	ptr->size = size;
	ptr->is_available = 0;
	ptr->next = (void*)((char*)ptr + SZ_PAGE + size);
	ptr = ptr->next;
	ptr->size = (2 * (type == TINY ? TINY_MAX : SMALL_MAX)) - size;
	ptr->is_available = 1;
	ptr->next = tmp->next;
//	resize_page(size); // resize le size de la premiere page et change la valeur de son next a page->next + 8 + size
	return ((void*)((char*)g_m_block + SZ_BLOCK + SZ_PAGE));*/
}

static size_t	check_available_memory(size_t size, size_t type)
{
	t_block	*ptr;
	size_t		i;

	if (!g_m_block || type == LARGE)
		return (0);
	ptr = g_m_block;
	i = 1;
	while (ptr)
	{
		if (((ptr->mapped_size == ((size_t)getpagesize() * TINY_N_PAGE) &&
			type == TINY) || (ptr->mapped_size == ((size_t)getpagesize() *
				SMALL_N_PAGE) && type == SMALL)) &&
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
/*
void			*create_and_queue_block(size_t size)
{
	t_g_m_block	*ptr;

	ptr = g_m_block;
	while (ptr->next)
		ptr = ptr->next;
	if ((ptr->next = (t_g_m_block *)mmap(0, to_map_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	ptr = ptr->next;
	ptr->pages = NULL;
	ptr->next = NULL;
	ptr->mapped_size = size;
	ptr->used_size = SZ_BLOCK;
}
*/
void			*malloc(size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size);
	size_t			type;
	size_t			n;

	if (!size)
		return (NULL);
	n = 0;
	type = get_map_type(aligned_size);
	if ((n = check_available_memory(aligned_size, type)))
	{
	//	if (type == LARGE)
	//		return (create_and_queue_block(ALIGN(ALIGN_GETPAGESIZE, size)));
	//	else
			return (find_and_insert_page(aligned_size, type, n)); // TODO queue it in send_memory_pointer if type == LARGE create a new and queue. TODO change name, maybe do a queue function and create?/ another or w/e
	}
	// TODO IF cant resize or break pages, call check_available_memory from block->n*next etc, if not possible  just do a new one.
	return (create_memory_block(aligned_size, type));
}
