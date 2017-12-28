/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_log_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:09:46 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/28 18:02:23 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (0);
	while (*s1)
	{
		if (*s1 != *s2)
			return (((unsigned char)*s1 - (unsigned char)*s2));
		++s1;
		++s2;
	}
	return ((*s1 - *s2));
}

static void	display_m_args(void *ptr, size_t size, size_t aligned_size, int fd)
{
	ft_putstr_fd(fd, "a size of ");
	ft_putnbr_fd(fd, size);
	if (size)
	{
		ft_putstr_fd(fd, " a mapped size of ");
		ft_putnbr_fd(fd, aligned_size);
		//ft_putnbr_hexa_fd(fd, size, 0);
	}
	ft_putstr_fd(fd, " and returning ");
	if (ptr)
		ft_putnbr_hexa_fd(fd, ptr, 1);
	else
		ft_putstr_fd(fd, "NULL\n");
}

//static void	display_f_args()

void		write_log_file(void *ptr, size_t size, size_t aligned_size, int f)
{
	int			fd;
	const char	*s = getenv("MEMORY_LOG_FILE");
	const char	ref[5] = {"Malloc", "Free", "Realloc", "Reallocf", "Calloc"};

	if (!s || ft_strcmp(s, "1") || f < MALLOC_REF || f > CALLOC_REF)
		return ;
	if ((fd = open(".memory.log", O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return ;
	if (f == REALLOC_REF || CALLOC_REF)
		ft_putstr_fd(fd, "\t");
	if (f == REALLOCF_REF)
		ft_putstr_fd(fd, "\t\t");
	ft_putstr_fd(fd, ref[f]);
	ft_putstr(" called with: "); // a mettre dans display_x_args ?
	if (f == MALLOC_REF)
		display_m_args(ptr, size, aligned_size, fd);
	//ft_putstr_fd(fd, "\n");// ?
	close(fd);
	}

	// todo faire une fonction ou une ref pour invalid ptr free ?