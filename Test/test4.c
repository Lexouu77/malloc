/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:51:08 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/23 23:44:15 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(void)
{
	int i;
	char *addr;
	char *adr;

	//i = 0;
	//while (i < 1)
	//{
		addr = (char*)malloc(1097);
		addr[0] = 42;
		adr = (char*)malloc(1080);
		addr = realloc(addr, 800);
		show_alloc_mem();
		addr = malloc(5);
		show_alloc_mem();

	//}
	//show_alloc_mem();
	return (0);
}