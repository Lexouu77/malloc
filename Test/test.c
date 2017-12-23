/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:39:55 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/23 20:40:37 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 5)
	{
		addr = (char*)malloc(1097);
		addr[0] = 42;
			addr = (char*)malloc(2997);
		
		addr[0] = 42;
	addr = (char*)malloc(5097);
		addr[0] = 42;
		i++;
	}
	show_alloc_mem();
	return (0);
}
/*
int main(void)
{
	char	*ptr;

	ptr = mmap(0, 40960, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_PRIVATE, -1, 0);
	munmap(ptr, 40960);
	
	return 0;
}*/
