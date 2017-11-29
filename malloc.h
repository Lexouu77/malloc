/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 10:04:32 by ahamouda          #+#    #+#             */
/*   Updated: 2017/11/29 18:34:27 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

# define ALIGN(alignement, size) (size_t)size + alignement - 1 & (size_t)~(alignement - 1) // alignement to 8 or 4096
# define ALIGN_MEMORY_BLOCK_64BIT 8
# define ALIGN_GETPAGESIZE getpagesize()

# define N_ALLOC_PAGES 100
# define TINY_MAX 1696
# define TINY_N_GETPAGESIZE 42
# define SMALL_MAX 4768
# define SMALL_N_GETPAGESIZE 117

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
** TODO Should i prefill it ?
*/

/*
**  
*/

typedef struct		s_m_zone
{
	size_t			alloced_size;
	size_t			used_size;
	struct s_page	*pages;
	struct s_m_zone	*next;
}					t_m_zone;

/*
** total memory size mapped (TODO w/ or w/o sizeof(struct)  ??? -> WITH TO BE UNMAPPED (SIZE)
** used_size.
** ptr to pages.
** next m_block
*/

void				*malloc(size_t size);

#endif
