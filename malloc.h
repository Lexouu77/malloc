/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:32 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/07 22:20:15 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define ALIGN(alignement, size) (size_t)size + alignement - 1 & (size_t)~(alignement - 1) // alignement to 8 or 4096
# define ALIGN_M_64BIT 8
# define ALIGN_GETPAGESIZE (size_t)getpagesize()

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

extern	struct s_block	*g_m_block;

typedef struct		s_page
{
	size_t			size;
	size_t			is_available;
	struct s_page	*next;
}					t_page;

/*
** >s_page_ptr<[size][is_available][next]..data
** sizeof of incoming data.
** is available
** TODO Should i prefill it ? y
** TODO faire une fonction resize page en changeant size et la valeur de next
*/

/*
**  
*/

typedef struct		s_block
{
	size_t			mapped_size;
	size_t			used_size;
	struct s_page	*pages;
	struct s_block	*next;
}					t_block;

/*
** total memory size mapped (TODO w/ or w/o sizeof(struct)  ??? -> WITH TO BE UNMAPPED (SIZE)
** used_size. 32
** ptr to pages.
** next m_block if next == NULL -> LARGE
*/

void				*create_memory_block(size_t size, size_t type); // realloc malloc
void				free(void *ptr);
size_t				get_map_type(size_t size); // realloc malloc
size_t				get_map_size(size_t size, size_t type); // show mem alloc memory
void				group_pages(t_block *block);
void				*insert_page(size_t size, void *ptr); // realloc
void				*malloc(size_t size);
void				*queue_block(t_block *new_block, size_t type); // realloc if not enough size.
void				*realloc(void *ptr, size_t size);

#endif
