/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:51:45 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 17:52:08 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

bool	is_in(char *str, char *set)
{
	int		i;
	int		j;
	int		count_check;

	if (!str || !set)
		exit_error("Error: Something went wrong!\n");
	i = 0;
	count_check = 0;
	while (set[i])
	{
		j = 0;
		while (str[j])
		{
			if (str[j] == set[i])
			{
				count_check++;
				break ;
			}
			j++;
		}
		i++;
	}
	if (count_check)
		return (true);
	return (false);
}
