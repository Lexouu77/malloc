/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 04:43:33 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/12 22:11:57 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static char	get_base_char(char c)
{
	if (c >= 10 && c <= 15)
		return (65 + (c - 10));
	return (48 + c);
}

char		*itoa_base(void *x, unsigned long base)
{
	char			str[32];
	int				size;
	unsigned long	nb;

	nb = (unsigned long long)x;
	size = 1; // + 2 ?
	while (nb /= base)
		++size;
	//str = 
	// bzero str
	nb = (unsigned long long)x;
	while (--size >= 0)
	{
		str[size] = get_base_char((char)(nb % base));
		nb /= base;
	}
	return (str);
}
