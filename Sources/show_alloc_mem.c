/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:38:59 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/25 18:41:07 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	display_pages(t_block *block)
{
	t_page	*ptr;
	size_t	size;

	size = 0;
	ptr = block->pages;
	while (ptr)
	{
		if (!ptr->is_available)
		{
			ft_putnbr_hexa((void*)ptr, 0);
			ft_putstr(" - ");
			ft_putnbr_hexa((void*)((char*)ptr + ptr->size), 0);
			ft_putstr(" : ");
			ft_putnbr(ptr->size);
			size += ptr->size;
			ft_putstr(" bytes\n");
		}
		ptr = ptr->next;
	}
	return (size);
}

static size_t	display_large(t_block *block)
{
	ft_putnbr_hexa((void*)block, 0);
	ft_putstr(" - ");
	ft_putnbr_hexa((void*)((char*)block + block->used_size), 0);
	ft_putstr(" : ");
	ft_putnbr(block->used_size);
	ft_putstr(" bytes\n");
	return (block->used_size);
}

void			show_alloc_mem(void)
{
	t_block		*block;
	size_t		total;

	if (!g_m_block)
		return ;
	pthread_mutex_lock(&g_m_mutex);
	total = 0;
	block = g_m_block;
	while (block)
	{
		if (block->pages && block->used_size == SZ_BLOCK)
		{
			block = block->next;
			continue ;
		}
		display_type_and_address(block);
		total += block->pages ? display_pages(block) : display_large(block);
		block = block->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr("bytes\n");
	pthread_mutex_unlock(&g_m_mutex);
}
