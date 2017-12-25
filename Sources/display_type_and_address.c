/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_type_and_address.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 14:59:06 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/23 21:08:54 by ahamouda         ###   ########.fr       */
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