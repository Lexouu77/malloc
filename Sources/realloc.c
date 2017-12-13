/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:35:35 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/13 19:53:08 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	is_mapped(void *ptr)
{
	t_block	*block;
	t_page	*page;

	if (!g_m_block)
		return (0);
	block = g_m_block;
	while (block->next)
	{
		if (ptr > (void*)block && ptr < (void*)block->next)
			break ;
		block = block->next;
	}
	if (!block->pages && (void*)ptr != (void*)block + SZ_BLOCK)
		return (0);
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

static size_t	is_remappable(void *ptr, size_t size)
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
	if (!block->pages && block->mapped_size >= size)
		return (1);
	page = block->pages;
	while (page->next)
	{
		if ((void*)ptr == (void*)page)
			break ;
		page = page->next;
	}
	if (block->used_size + (size - page->size) <= block->mapped_size ||
			page->size >= size || check_next_pages(page, size))
		return (1);
	return (0);
}

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


// if LARGE and enough size, don't free., but memcpy ?
void			*realloc(void *ptr, size_t size)
{
	const size_t	aligned_size = ALIGN(ALIGN_M_64BIT, size); // no need to call get_map_size cause malloc.
	void			*mapped_ptr;

	if (!ptr && !size)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	if (!is_mapped(ptr))
		return (malloc(size));
	if (is_remappable(ptr, aligned_size))
		return (remap_block(ptr, aligned_size)); // change g_m_block to block then call malloc then switch back ?
	if (!(mapped_ptr = malloc(aligned_size)))
		return (NULL);
	//TODO memcpy
	free(ptr);
	return (mapped_ptr);
}

/*
** NULL NULL -> NULL
** NULL x -> malloc(size)
** x NULL -> free(ptr)
** x x -> malloc memcpy free
** if ptr is invalid -> undefined behavior. in my case. return malloc(size)
*/
