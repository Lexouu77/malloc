/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/05 04:43:04 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/28 16:28:31 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void			ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

void			ft_putstr_fd(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}
