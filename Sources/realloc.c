/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/17 20:20:39 by ahamouda         ###   ########.fr       */
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
		return (((void*)ptr == (void*)block + SZ_BLOCK) ? 1 : 0);
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
/*
static size_t	check_next_pages(t_page *page, size_t size)
{
	size_t	total_size;

	if (!page->next)
		return (0);
	total_size = page->size;
	while (page->next)
	{
		if (!page->next->is_available)
			break ;
		page = page->next;
	}
	if (total_size >= size)
		return (1);
	return (0);
}

// TODO if page..[<SZ_PAGE][next]
// add la size superflue a la page.
*/
static size_t	is_remappable(void *ptr, size_t size)
{
	const t_block	*block = get_block(ptr);
	t_page			*page;

	if (!page)
		return ((block->mapped_size - SZ_BLOCK >= size) ? 1 : 0);
	//group_pages(block);
	page = get_page(ptr, block);
	if (page->size >= size) // return ptr.
		return (1);
	if (!page->next || (page->next && !page->next->is_available)) // new
		return (0);
	if (page->next->is_available
		&& page->next->size + page->size + SZ_PAGE >= size) // remap
		return (1);
	return (0);
}
/*
// TODO Faire une fonction get block(ptr)
// retournant le block contenant cett adresse.

static void		fusion_pages(t_block *block, t_page *page, size_t size)
{
	t_page	*tmp;

	block->used_size = block->used_size - page->size + size;
	page->size += page->next->size + SZ_PAGE;
	page->next = page->next->next;
	// todo created next if possible (if page->size - size - SZ_PAGE >= 8 created next else nope and leave.
}
*/

static void		*remap_block(void *ptr, size_t size)
{
	const	t_block	*block = get_block(ptr);
	t_page			*page;

	page = get_page(block);
	if (!block->pages || page->size >= size)
		return (ptr);
	
}

/*
static void		*remap_block(void *ptr, size_t size)
{
	t_block	*block;
	t_page	*page;

	block = g_m_block;
	while (block->next)
	{
		if (ptr > (void*)block && ptr < (void*)block->next)
			break ;
		block = block->next;
	}
	if (!block->pages)
		block->used_size = size; // TODO for showallocmem.
	if (!block->pages)
		return (ptr);
	page = block->pages;
		while (page->next)
	{
		if ((void*)ptr == (void*)page)
			break ;
		page = page->next;
	}
		// group_pagespage?
	fusion_pages(block, page, size);
	return (ptr);
}


*/
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
	if (is_remappable(ptr, size))
		return (remap_block(ptr, size));
	if ((mapped_ptr = malloc(size)))
	{
		ft_memcpy(mapped_ptr, ptr, size);
		free(ptr);
	}
	return (mapped_ptr);
}

/*
** OK NULL x -> malloc(size)
** OK x NULL -> free(ptr)
** x x -> malloc memcpy free or return same ptr after remap(or not).
** OK if ptr is invalid -> undefined behavior. in my case. return malloc(size)
*/
