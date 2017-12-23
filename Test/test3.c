/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:51:08 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/23 21:05:12 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 10)
	{
		addr = (char*)malloc(1097);
		addr[0] = 42;
		free(addr);
		addr = (char*)malloc(2997);
		addr[0] = 42;
		free(addr);
		addr = (char*)malloc(5097);
		addr[0] = 42;
		free(addr);
		i++;
	}
	show_alloc_mem();
	return (0);
}