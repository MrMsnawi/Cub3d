/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:50:48 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 09:51:01 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	ft_free(void)
{
	t_mem_t	**col;
	t_mem_t	*curr;
	t_mem_t	*tmp;

	col = get_collector();
	if (!col)
		return ;
	curr = *col;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->ptr);
		tmp = NULL;
		free(tmp);
		tmp = NULL;
	}
	*col = NULL;
}
