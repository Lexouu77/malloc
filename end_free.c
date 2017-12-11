/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 21:02:34 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/11 21:04:23 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
