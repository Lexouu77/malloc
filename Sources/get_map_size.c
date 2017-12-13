/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 21:33:46 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/12 21:34:05 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			get_map_size(size_t size, size_t type)
{
	if (type == TINY)
		return ((size_t)getpagesize() * TINY_N_PAGE);
	if (type == SMALL)
		return ((size_t)getpagesize() * SMALL_N_PAGE);
	return (ALIGN((size_t)getpagesize(), size + SZ_BLOCK)); // remove SZ_BLOCK if showmemalloc ?
}
