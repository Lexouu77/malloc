/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:02:03 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/11 19:00:22 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>

//TODO display nb of pages showall

void				group_pages(t_block *block)
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
		ptr->size += ptr->next->size + SZ_PAGE;
		ptr->next = ptr->next->next;
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

static size_t		set_available(t_block *block, void *ptr)
{
	t_page	*page;

	if (!block->pages)
		return ((void*)ptr == (void*)((char*)block + SZ_BLOCK) ? 0 : 1);
//	printf("PRE OK\n");
	page = block->pages;
	while (page->next)
	{
//		printf("%p - %p - %p\n",g_m_block, ptr, (void*)((char*)page + SZ_PAGE));
		if ((void*)ptr == (void*)((char*)page + SZ_PAGE))
			break ;
		page = page->next;
	}
	if ((void*)ptr != (void*)((char*)page + SZ_PAGE))
		return (1);
//	printf("LALALA\n");
	page->is_available = 1;
	block->used_size -= (SZ_PAGE + page->size);
	return (0);
}
/*
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
*/
void			ffree(void *ptr) // TODO add un arg pour specifier si force unmap.pour realloc ?
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
	if (set_available(block, ptr))
		return ;
	if (is_unmappable(block)) // check LARGE // TODO munmap large.
	{
//		cut_link(block);
	//	munmap(block, block->mapped_size);
	}
	else
		group_pages(block);
}

void		end_free(void)
{
	t_block	*block;
	size_t	*total_size;

	if (!g_m_block)
		return ;
	total_size = 0;
	block = g_m_block;
	while (block)
	{
		total_size += block->mapped_size;
		block = block->next;
	}
	munmap(block, block->mapped_size);
}
