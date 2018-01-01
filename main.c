/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 17:33:11 by ahamouda          #+#    #+#             */
/*   Updated: 2018/01/01 17:42:24 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	char	*addr;

	//addr = (char*)malloc(1024);
	addr = (char*)malloc(1024);
	addr[0] = 42;
	//free(addr);
//	show_alloc_mem_more();
	return (0);
}