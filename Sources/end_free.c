/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:39:16 by ahamouda          #+#    #+#             */
/*   Updated: 2018/01/01 17:57:59 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		end_free(void)
{
	t_block	*block;
	t_block	*to_kill;

	if (!g_m_block)
		return ;
	block = g_m_block;
	while (block)
	{
		to_kill = block;
		block = block->next;
		munmap(to_kill, to_kill->mapped_size);
	}
	return ;
}
