/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:26:57 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 18:20:17 by ahamouda         ###   ########.fr       */
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
		// ptr = malloc(TINY_MAX - 2);
		// ptr = malloc(TINY_MAX - 2);
		ptr = malloc(TINY_MAX - 32);
		ptr = malloc(32);
		ptr = malloc(16);
		ptr = malloc(32);
		free(ptr);
	//	ptr = realloc(ptr, SMALL_MAX); // memcpy
		//ptr = realloc(ptr, 30); // underflow
		//free(ptr);
		//if (i % NB_THREADS == 0)
			//show_alloc_mem();
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