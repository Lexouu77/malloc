/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mapped.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:20:54 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/25 18:21:11 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			is_mapped(void *ptr)
{
	t_block	*block;
	t_page	*page;

	if (!(block = get_block(ptr)))
		return (0);
	if (!block->pages)
		return (((void*)ptr == (void*)((char*)block + SZ_BLOCK)) ? 1 : 0);
	page = block->pages;
	while (page->next)
	{
		if ((void*)ptr == (void*)((char*)page + SZ_PAGE))
			break ;
		page = page->next;
	}
	if ((void*)ptr != (void*)((char*)page + SZ_PAGE))
		return (0);
	return (1);
}
