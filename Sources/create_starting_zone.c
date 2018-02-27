/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_starting_zone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:36:00 by ahamouda          #+#    #+#             */
/*   Updated: 2018/02/27 17:38:53 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	create_starting_zone(void)
{
	if ((g_m_block = (t_block *)mmap(0, (size_t)getpagesize(), PROT_READ |
		PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		g_m_block = NULL;
		return ;
	}
	g_m_block->mapped_size = (size_t)getpagesize();
	g_m_block->used_size = SZ_BLOCK;
	g_m_block->pages = (void*)((char*)g_m_block + SZ_BLOCK);
	g_m_block->next = NULL;
	g_m_block->pages->size = g_m_block->mapped_size - g_m_block->used_size;
	g_m_block->pages->is_available = 1;
	g_m_block->pages->next = NULL;
}
