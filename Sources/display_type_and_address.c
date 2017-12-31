/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type_and_address.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:59:06 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 17:27:58 by ahamouda         ###   ########.fr       */
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

static void	display_used_max(t_block *block, t_alloc_mem *m_info)
{
	if (!m_info->display)
		return ;
	if (!block->pages)
		ft_putstr("LARGE : ");
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
		ft_putstr("TINY  : ");
	else
		ft_putstr("SMALL : ");
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
	m_info->total_used += block->used_size;
	if (!block->pages)
	{
		display_used_max(block, m_info);
		m_info->n_large++;
	}
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
	{
		display_used_max(block, m_info);
		m_info->n_tiny++;
	}
	else
	{
		display_used_max(block, m_info);
		m_info->n_small++;
	}
}
