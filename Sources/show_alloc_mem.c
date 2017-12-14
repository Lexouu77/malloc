/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:38:59 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/14 21:45:53 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#include <stdio.h>
// remove it.

static void display_address(t_block *block)
{
	printf("%p\n", (void*)block);
	ft_putstr("0x");
	ft_putnbr_hexa((size_t)block);
	ft_putchar('\n');
}

static void	display_type(t_block *block)
{
	if (!block->pages)
		ft_putstr("LARGE : ");
	else if (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
		ft_putstr("TINY : ");
	else
		ft_putstr("SMALL : ");
}

void		show_alloc_mem(void)
{
	t_block		*block;
	//t_page		*page;

	if (!g_m_block)
	return ;
	block = g_m_block;
	while (block)
	{
		display_type(block);
		display_address(block);

		block = block->next;
	}

}
