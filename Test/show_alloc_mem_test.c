/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 17:52:42 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 18:01:34 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
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