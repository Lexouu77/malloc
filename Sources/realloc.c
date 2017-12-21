/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/21 21:36:34 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	is_mapped(void *ptr)
{
	t_block	*block;
	t_page	*page;

	if (!(block = get_block(ptr)))
		return (0);
	if (!block->pages)
		return (((void*)ptr == (void*)((char*)block + SZ_BLOCK)) ? 1 : 0);
	page = block->pages;
	while (page->next)
	{
		if ((void*)ptr == (void*)page)
			break ;
		page = page->next;
	}
	if ((void*)ptr != (void*)page)
		return (0);
	return (1);
}

static size_t	is_remappable(void *ptr, size_t size)
{
	t_block			*block;
	t_page			*page;

 	block = get_block(ptr);
	if (!block->pages)
		return ((block->mapped_size - SZ_BLOCK >= size) ? 1 : 0);
	//group_pages(block);
	page = get_page(ptr, block);
	if (page->size >= size) // return ptr.
		return (1);
	if (!page->next || (page->next && !page->next->is_available)) // new
		return (0);
	if (page->next->is_available
		&& page->next->size + page->size >= size) // remap
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
		return (ptr);
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
		return (ptr);
	}
	page->size += page->next->size;
	block->used_size += SZ_PAGE + page->next->size;
	page->next = page->next->next;
	return (ptr);
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
	if (block->mapped_size == (size_t)getpagesize() * SMALL_N_PAGE && type == SMALL)
		return (1);
	if (block->mapped_size == (size_t)getpagesize() * TINY_N_PAGE && type == TINY)
		return (1);
	return (0);
}

void			*realloc(void *ptr, size_t size)
{
	void			*mapped_ptr;

	if (!ptr || !is_mapped(ptr))
		return (malloc(size));
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (is_same_type(ptr, size) && is_remappable(ptr, size))
		return (remap_block(ptr, size));
	if ((mapped_ptr = malloc(size)))
	{
		ft_memcpy(mapped_ptr, ptr, size);
		free(ptr);
	}
	return (mapped_ptr);
}

/*
** NULL x -> malloc(size)
** x NULL -> free(ptr)
** x x -> malloc memcpy free or return same ptr after remap(or not).
** if ptr is invalid -> undefined behavior. in my case. return malloc(size)
** if you're realloacing differents types, you'll get a new malloced part.
*/
