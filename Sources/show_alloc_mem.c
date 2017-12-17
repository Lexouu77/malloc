/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:38:59 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/17 17:31:49 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	display_pages(t_block *block, size_t b)
{
	t_page	*ptr;
	size_t	size;

	if (b)
		b = 0;
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

static size_t	display_not_pages(t_block *block, size_t b)
{
	if (b)
		b = 0;
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
	total = 0;
	block = g_m_block;
	while (block)
	{
		display_type_and_address(block, DISPLAY_MORE);
		if (block->pages)
		 	total += display_pages(block, DISPLAY_MORE);
		else
			total += display_not_pages(block, DISPLAY_MORE);
		block = block->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr("bytes\n");
}
