/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:20:37 by abmasnao          #+#    #+#             */
/*   Updated: 2025/12/12 16:20:55 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

int	map_in(char *file, int i)
{
	int	new;

	new = 0;
	while (file[i])
	{
		if (file[i] == '\n')
			new = 1;
		if (new == 1)
		{
			i++;
			while (ft_isspace(file[i]))
				i++;
			if (file[i] == '1' || file[i] == '0')
				return (i);
			else
				new = 0;
		}
		i++;
	}
	return (-1);
}

int	is_splitted_map(char *file)
{
	int	i;

	if (!file)
		exit_error("Error: something went wrong\n");
	i = map_in(file, 0);
	if (i == -1)
		return (1);
	while (file[i])
	{
		if (file[i] == '\n' && file[i - 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
