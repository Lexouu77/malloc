/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:02:03 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/07 20:27:13 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//TODO display nb of pages showall

static void		group_pages(t_block *block)
{
	t_page	*ptr;

	ptr = block->pages;
	while (ptr && ptr->next)
	{
		if (!ptr->is_available || !ptr->next->is_available)
		{
			ptr = ptr->next;
			continue ;
		}
		ptr->next = ptr->next->next;
		ptr->size += ptr->next->size + SZ_PAGE;
	}
}

static size_t		is_unmappable(t_block *block)
{
	if (!block->pages)
		return (1);
	if (block->used_size == SZ_BLOCK)
		return (1);
	return (0);
}

static size_t		set_unavailable(t_block *block, void *ptr)
{
	t_page	*page;

	if (!block->pages && (void*)ptr != (void*)block + SZ_BLOCK)
		return (1);
	page = block->pages;
	while (page->next)
	{
		if ((void*)ptr == (void*)page)
			break ;
		page = page->next;
	}
	if ((void*)ptr != (void*)page)
		return (1);
	page->is_available = 1;
	block->used_size -= (SZ_PAGE + page->size);
	return (0);
}

static void		cut_link(t_block *block)
{
	t_block	*ptr;

	if (block == g_m_block)
		g_m_block = block->next;
	else
	{
		ptr = g_m_block;
		while (ptr->next && ptr->next != block)
			ptr = ptr->next;
		ptr->next = block->next;
	}
}

void			free(void *ptr) // TODO add un arg pour specifier si force unmap.pour realloc ?
{
	t_block	*block;

	if (!ptr || !g_m_block) // nice try.
		return ;
	block = g_m_block;
	while (block->next)
	{
		if (ptr > (void*)block && ptr < (void*)block->next) // >= ? no. // OR ptr > block && ptr < block + block->mapped_size?
			break ;
		block = block->next;
	}
	if (set_unavailable(block, ptr))
		return ;
	if (is_unmappable(block)) // check LARGE
		cut_link(block);
	else
		group_pages(block);
	munmap(block, block->mapped_size);
}
