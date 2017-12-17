/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapped_size_and_type.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 15:53:54 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/17 15:54:06 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			check_mapped_size_and_type(t_block *ptr, size_t size, size_t type)
{
	if (size + SZ_PAGE > ptr->mapped_size - ptr->used_size)
		return (0);
	if (type == TINY && ptr->mapped_size == TINY_N_PAGE * (size_t)getpagesize())
		return (1);
	if (type == SMALL && ptr->mapped_size == SMALL_N_PAGE * (size_t)getpagesize())
		return (1);
	return (0);
}
