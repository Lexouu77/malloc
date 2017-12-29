/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:32 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/29 17:20:18 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>
# include <pthread.h>
# include <fcntl.h>

# include <stdio.h> //to del

# define ALIGN(algt, size) (size_t)size + algt - 1 & (size_t)~(algt - 1)
# define ALIGN_M_64BIT 8

/*
** # define ALIGN_GETPAGESIZE (size_t)getpagesize()
*/

# define N_MIN_ALLOC 100

# define TINY_MAX (size_t)1696
# define TINY_N_PAGE 42

/*
** (SZ_BLOCK + (N_MIN_ALLOC * SZ_PAGE) + (N_MIN_ALLOC * TINY_MAX)) / getpagesize
** = TINY_N_PAGE
** TODO Change TINY_N_PAGE par ce machin ?
*/

# define SMALL_MAX (size_t)4768
# define SMALL_N_PAGE 117

# define SZ_BLOCK sizeof(t_block)
# define SZ_PAGE sizeof(t_page)

# define TINY 1
# define SMALL 2
# define LARGE 3

# define HEXATABLE "0123456789ABCDEF"

# define MALLOC_REF 1
# define FREE_REF 2
# define REALLOC_REF 3
# define REALLOCF_REF 4
# define CALLOC_REF 5

extern	struct s_block		*g_m_block;
extern	pthread_mutex_t		g_m_mutex;

typedef struct		s_page
{
	size_t			size;
	size_t			is_available;
	struct s_page	*next;
}					t_page;

typedef struct		s_block
{
	size_t			mapped_size;
	size_t			used_size;
	struct s_page	*pages;
	struct s_block	*next;
}					t_block;

void				*calloc(size_t count, size_t size);
size_t				check_mapped_size_and_type(t_block *p, size_t size,
					size_t type);

void				display_type_and_address(t_block *block);
void				end_free(void) __attribute__((destructor));
void				free(void *ptr);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_putchar(char c);
void				ft_putchar_fd(int fd, char c);
void				ft_putnbr_hexa(void *ptr, size_t line_feed);
void				ft_putnbr_hexa_fd(int fd, void *ptr, size_t line_feed);
void				ft_putnbr(size_t nb);
void				ft_putnbr_fd(int fd, size_t nb);
void				ft_putstr(const char *s);
void				ft_putstr_fd(int fd, const char *s);
void				*get_block(void *ptr);
void				*get_page(void *ptr, t_block *block);
size_t				get_map_size(size_t size, size_t type);
size_t				get_map_type(size_t size);
void				group_pages(t_block *block);
size_t				is_mapped(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*reallocf(void *ptr, size_t size);
void				show_alloc_mem(void);
void				write_log_file(void *ptr, size_t size, size_t aligned_size,
					int f);

#endif
