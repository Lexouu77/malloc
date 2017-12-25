/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 14:53:19 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/25 15:08:45 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <pthread.h>
#include <stdio.h>

int main(void)
{
	pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	int x;

	printf("t\n");
	x = pthread_mutex_lock(&mutex);
	printf("??%d\n", x);
	x = pthread_mutex_trylock(&mutex);
	printf("??%d\n", x);
	pthread_mutex_unlock(&mutex);
}