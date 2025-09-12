/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txtr_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:31:18 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 21:25:31 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

bool	corr_elmnt(char *elmnt)
{
	if (!elmnt)
		exit_error("Error: something went wrong!\n");
	return (ft_strncmp(elmnt, "NO", 2) == 0
		|| ft_strncmp(elmnt, "SO", 2) == 0
		|| ft_strncmp(elmnt, "WE", 2) == 0
		|| ft_strncmp(elmnt, "EA", 2) == 0);
}

int	get_line_index(char **data, char *elmnt)
{
	int	i;
	int	offset;

	if (!data || !*data || !elmnt)
		exit_error("Error: something went wrong!\n");
	i = 0;
	while (data[i])
	{
		offset = mo_wspaces(data[i]);
		if (ft_strncmp(data[i] + offset, elmnt, ft_strlen(elmnt)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

bool	extension_check(char *path)
{
	size_t	len;

	if (!path)
		exit_error("Error: something went wrong!\n");
	len = ft_strlen(path);
	if (len < 4)
		exit_error("Error: string lenght smaller than expected!\n");
	return (path[len - 4] == '.'
		&& path[len - 3] == 'x'
		&& path[len - 2] == 'p'
		&& path[len - 1] == 'm');
}

char	*parse_value(char *value)
{
	int		fd;
	int		i;
	char	*val;
	int		j;

	// printf("%s\n", value);
	if (!value)
		exit_error("Error: Something went wrong!\n");
	i = ft_strlen(value) - 1;
	while (i >= 0 && ft_isspace(value[i]))
		i--;
	val = ft_malloc(i + 1);
	if (!val)
		exit_error("Error: invalid pointer!\n");
	j = 0;
	while (j <= i)
	{
		val[j] = value[j];
		j++;
	}
	val[j] = '\0';
	fd = open(val, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		exit_error("Error: invalid texture path!\n");
	}
	close(fd);
	if (!extension_check(val))
		exit_error("Error: invalid texture extension (.xpm)\n");
	return (val);
}

char	*get_element_value(t_data *data, char *elmnt)
{
	int		line_index;
	int		line_col;
	char	*value;

	value = NULL;
	line_index = 0;
	line_col = 0;
	if (!data || !elmnt)
		exit_error("Error: something went wrong!\n");
	if (corr_elmnt(elmnt))
	{
		line_index = get_line_index(data->file_data, elmnt);
		if (-1 == line_index)
			exit_error("Error: can't find elmnt index!\n");
		line_col += ft_strlen(elmnt) + mo_wspaces(data->file_data[line_index]);
		line_col += mo_wspaces(data->file_data[line_index] + line_col);
		value = parse_value(data->file_data[line_index] + line_col);
	}
	return (value);
}
