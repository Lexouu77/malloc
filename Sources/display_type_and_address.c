/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type_and_address.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:59:06 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 16:05:47 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		display_type_and_address(t_block *block)
{
	if (!block->pages)
	{
		ft_putstr("LARGE : ");
		ft_putnbr_hexa(block, 1);
	}
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
	{
		ft_putstr("TINY  : ");
		ft_putnbr_hexa(block, 1);
	}
	else
	{
		ft_putstr("SMALL : ");
		ft_putnbr_hexa(block, 1);
	}
}

static void	display_used_max(t_block *block)
{
	ft_putnbr_hexa(block, 0);
	ft_putstr(" [");
	ft_putnbr(block->used_size);
	ft_putchar('/');
	ft_putnbr(block->mapped_size);
	ft_putstr("]\n");
}

void		display_type_and_address_more(t_block *block, t_alloc_mem *m_info)
{
	m_info->total_size += block->mapped_size;
	if (!block->pages)
	{
		ft_putstr("LARGE : ");
		display_used_max(block);
		m_info->n_large++;
		m_info->total_used += block->mapped_size;
	}
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
	{
		ft_putstr("TINY  : ");
		display_used_max(block);
		m_info->n_tiny++;
		m_info->total_used += block->used_size;
	}
	else
	{
		ft_putstr("SMALL : ");
		display_used_max(block);
		m_info->n_small++;
		m_info->total_used += block->used_size;
	}
}
