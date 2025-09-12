/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 07:43:59 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 09:53:13 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

t_mem_t	**get_collector(void)
{
	static t_mem_t	*col;

	return	(&col);
}

void	*ft_malloc(size_t size)
{
	t_mem_t	**col;
	t_mem_t	*alloc;
	void	*ptr;

	col = get_collector();
	ptr = malloc(size);
	if (!ptr)
		exit_error("Error: malloc failed!\n");
	alloc = malloc(sizeof(t_mem_t));
	if (!alloc)
		exit_error("Error: malloc failed!\n");
	alloc->ptr = ptr;
	alloc->next = *col;
	*col = alloc;
	return (ptr);
}
