/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:03:24 by ahamouda          #+#    #+#             */
/*   Updated: 2017/11/29 22:39:41 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"

int main(void)
{
//	struct rlimit	t;
	t_page			l;
	int				*p;
	int		*x;
	void	*q;
/*
	printf("r = %d\n", *(int*)malloc(0));

	printf("%zu\n", -1);
	printf("%zu - %zu\n", sizeof(t_m_zone), sizeof(t_page));
	printf("pagesize %d\n", getpagesize());
//	p = malloc(3);
//	printf("%d\n", p);

	l.size = 3446449;
	l.is_available = 4;
	x = (int*)(void*)&l;
	q= &l;
	printf("%d\n", *x);
	printf("ptr value %p\n", q);
	q++;
	printf("ptr value %p\n", q);
	printf("lsize value %d\n", &l.size);
	printf("lisavailable value %d\n", &l.is_available);
	printf("size %zd\n", sizeof(size_t));
	x += 2;
	printf("%d\n", *x);
//	printf("%d\n", *x + sizeof(size_t));

//	printf("%d\n", *((void*)l));

	printf("zzzz%zu\n", ALIGN(31));
*/
	t_m_zone t;
	printf("%d\n", &t);
	printf("%d\n", ((void*)&t + 32));
	return 0;
}
