/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_u_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:59:08 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 18:01:00 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub.h"

size_t	rgb_len(char *value, int offset)
{
	int	i;

	i = offset;
	while (value[i] && value[i] != ',' && !ft_isspace(value[i]))
		i++;
	return (i - offset);
}

int	num_len(char *str)
{
	int	i;
	int	count;

	if (!str)
		exit_error("Error: something went wrong!\n");
	i = 0;
	count = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			count++;
		i++;
	}
	return (count);
}

int	a_to_rgb_i(char *str)
{
	int	i;
	int	res;

	if (!str)
		exit_error("Error: something went wrong!\n");
	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			exit_error("Error: rgb range: 0...255\n");
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	if (str[i] != '\0' && !(str[i] >= '0' && str[i] <= '9'))
		exit_error("Error: invalid rgb character!\n");
	if (res > 255)
		exit_error("Error: rgb range: 0...255\n");
	return (res);
}
