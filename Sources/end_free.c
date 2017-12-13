/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:39:16 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/13 19:04:10 by ahamouda         ###   ########.fr       */
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
}
