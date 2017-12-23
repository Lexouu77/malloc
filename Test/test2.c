/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 20:51:08 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/23 21:58:28 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main(void)
{
	char *addr;

	addr = (char*)malloc(1097);
	addr[0] = 42;
	show_alloc_mem();
	addr = realloc(addr, 1200);
	show_alloc_mem();
	return (0);
}