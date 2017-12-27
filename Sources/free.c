/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 20:02:03 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/27 18:31:34 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	{
		if ((void*)ptr != (void*)((char*)block + SZ_BLOCK))
			pthread_mutex_unlock(&g_m_mutex);
		return ((void*)ptr == (void*)((char*)block + SZ_BLOCK) ? 0 : 1);
	}
	page = block->pages;
	while (page->next)
	{
		if ((void*)ptr == (void*)((char*)page + SZ_PAGE))
			break ;
		page = page->next;
	}
	if ((void*)ptr != (void*)((char*)page + SZ_PAGE))
	{
		pthread_mutex_unlock(&g_m_mutex);
		return (1);
	}
	page->is_available = 1;
	block->used_size -= (SZ_PAGE + page->size);
	return (0);
}

static void			cut_link(t_block *block)
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

void				free(void *ptr)
{
	t_block	*block;

	if (!ptr || !g_m_block)
		return ;
	pthread_mutex_lock(&g_m_mutex);
	block = g_m_block;
	while (block->next)
	{
		if (ptr > (void*)block && ptr < (void*)block->next)
			break ;
		block = block->next;
	}
	if (set_available(block, ptr))
	{
		pthread_mutex_unlock(&g_m_mutex);
		return ;
	}
	if (is_unmappable(block))
	{
		if (!block->pages)
		{
			cut_link(block);
			munmap(block, block->mapped_size);
		}
	}
	else
		group_pages(block);
	pthread_mutex_unlock(&g_m_mutex);
}
