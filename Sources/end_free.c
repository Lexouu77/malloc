/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 18:39:16 by ahamouda          #+#    #+#             */
/*   Updated: 2018/02/27 16:48:37 by ahamouda         ###   ########.fr       */
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

/*
** We could add every mapped_size and do one munmap.
** But memory could be not continuous so nope.
*/
