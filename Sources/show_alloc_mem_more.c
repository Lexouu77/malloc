/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_more.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamouda <ahamouda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 15:01:29 by ahamouda          #+#    #+#             */
/*   Updated: 2017/12/31 17:42:22 by ahamouda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		display_pages_more(t_block *block, t_alloc_mem *m_info)
{
	t_page	*ptr;
	int		i;

	i = (block->mapped_size == TINY_N_PAGE * (size_t)getpagesize()) ? 1 : 0;
	ptr = block->pages;
	while (ptr)
	{
		if (!ptr->is_available)
		{
			m_info->n_alloc++;
			i ? m_info->n_tiny_alloc++ : m_info->n_small_alloc++;
			if (m_info->display)
			{
				ft_putnbr_hexa((void*)ptr, 0);
				ft_putstr(" - ");
				ft_putnbr_hexa((void*)((char*)ptr + ptr->size), 0);
				ft_putstr(" : ");
				ft_putnbr(ptr->size);
				ft_putstr(" bytes\n");
			}
		}
		ptr = ptr->next;
	}
}

static void		display_large_more(t_block *block, t_alloc_mem *m_info)
{
	m_info->n_alloc++;
	m_info->n_large_alloc++;
	if (!m_info->display)
		return ;
	ft_putnbr_hexa((void*)block, 0);
	ft_putstr(" - ");
	ft_putnbr_hexa((void*)((char*)block + block->used_size), 0);
	ft_putstr(" : ");
	ft_putnbr(block->used_size);
	ft_putstr(" bytes\n");
}

static void		init_m_info(t_alloc_mem *m_info)
{
	char	*s;

	s = getenv("M_DISPLAY");
	if (s && s[0] == '1')
		m_info->display = 1;
	else
		m_info->display = 0;
	m_info->total_size = 0;
	m_info->total_used = 0;
	m_info->n_alloc = 0;
	m_info->n_tiny_alloc = 0;
	m_info->n_small_alloc = 0;
	m_info->n_large_alloc = 0;
	m_info->n_tiny = 0;
	m_info->n_small = 0;
	m_info->n_large = 0;
}

static void		display_all_info(t_alloc_mem m_info)
{
	ft_putstr("\nMemory      : [");
	ft_putnbr(m_info.total_used);
	ft_putchar('/');
	ft_putnbr(m_info.total_size);
	ft_putstr("]\nFree memory : [");
	ft_putnbr(m_info.total_size - m_info.total_used);
	ft_putstr("]\nTotal pages : [");
	ft_putnbr(m_info.total_size / (size_t)getpagesize());
	ft_putstr("]\nNumber of allocation   [Tiny|Small|Large] [");
	ft_putnbr(m_info.n_tiny_alloc);
	ft_putchar('|');
	ft_putnbr(m_info.n_small_alloc);
	ft_putchar('|');
	ft_putnbr(m_info.n_large_alloc);
	ft_putstr("]\nNumber of memory block [Tiny|Small|large] [");
	ft_putnbr(m_info.n_tiny);
	ft_putchar('|');
	ft_putnbr(m_info.n_small);
	ft_putchar('|');
	ft_putnbr(m_info.n_large);
	ft_putstr("]\n");
}

void			show_alloc_mem_more(void)
{
	t_block		*block;
	t_alloc_mem	m_info;

	if (!g_m_block)
		return ;
	pthread_mutex_lock(&g_m_mutex);
	init_m_info(&m_info);
	block = g_m_block;
	while (block)
	{
		display_type_and_address_more(block, &m_info);
		if (block->pages)
			display_pages_more(block, &m_info);
		else
			display_large_more(block, &m_info);
		block = block->next;
	}
	display_all_info(m_info);
	pthread_mutex_unlock(&g_m_mutex);
}
