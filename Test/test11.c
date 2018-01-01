/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:26:57 by ahamouda          #+#    #+#             */
/*   Updated: 2018/01/01 16:07:52 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define NB_THREADS 42

static void	*thread_foo(void *arg)
{
	int		i;
	void	*ptr;

	i = 0;
	(void)arg;
	while(i < NB_THREADS * 10)
	{
		ptr = calloc(16, 42);
        ptr = calloc(136, 432);
        ptr = reallocf(ptr, 434342343);
        ptr = malloc(16);
        ptr = malloc(32);
        ptr = reallocf(ptr, 42);
        free(ptr);
		i++;
	}
	//		show_alloc_mem();
	return (NULL);
}

int	multi_thread_test(void)
{
	pthread_t	threads[NB_THREADS];
	int			i;

	i = 0;
	while (i < NB_THREADS)
	{
		pthread_create(&threads[i],NULL,thread_foo, NULL);
		i++;
	}
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

int main(void)
{
	multi_thread_test();
	return (0);
}