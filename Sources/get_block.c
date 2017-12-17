/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:35:04 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/17 19:44:12 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	}
	if (ptr > (void*)block && ptr < (void*)((char*)block + block->mapped_size))
		return (block);
	return (NULL);
}

void			*get_page(void*ptr, t_block *block)
{
	t_page	*page;

	page = block->pages;
	while (page)
	{
		if ((void*)page == ptr)
			break ;
		page = page->next;
	}
	return ((void*)page);
}
