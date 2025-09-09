/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:11:25 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 17:42:18 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

bool	valid_char_name(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

void	path_parse(char *path)
{
	int		pfd;
	size_t	len;

	if (!path)
		exit_error("Error: Somthing went wrong!\n");
	len = ft_strlen(path);
	pfd = open(path, O_RDONLY);
	if (pfd < 0)
		exit_error("Error: (check existance|read permission)\n");
	close(pfd);
	if(!path[len - 5] || (!valid_char_name(path[len - 5])))
		exit_error("Error: incomplete name!\n");
	if (path[len - 4] != '.' || path[len - 3] != 'c'
		|| path[len - 2] != 'u' || path[len - 1] != 'b')
		exit_error("Error: invalid extension! (.cub)\n");
}

void	*ft_realloc(char *old_ptr, size_t new_size)
{
	int		i;
	char	*ptr;

	ptr = (char *)malloc(new_size);
	if (!ptr)
		return (NULL);
	i = 0;
	if (old_ptr)
	{
		while (old_ptr[i])
		{
			ptr[i] = old_ptr[i];
			i++;
		}
		ptr[i] = '\0';
		free(old_ptr);
		old_ptr = NULL;
	}
	return (ptr);
}

char	*get_file_content(int fd)
{
	char	c;
	int		i;
	char	*buf;
	int		counter;
	
	i = 0;
	buf = NULL;
	counter = 1;
	while (counter > 0)
	{
		buf = ft_realloc(buf, i + 2);
		if (!buf)
		{
			close(fd);
			exit_error("Error: ft_realloc failed!\n");
		}
		counter = read(fd, &c, 1);
		if (counter == 0)
			break ;
		if (counter < 0)
		{
			free(buf);
			close(fd);
			exit_error("Error: read failed!\n");
		}
		buf[i] = c;
		buf[i + 1] = '\0';
		i++;
	}
	close(fd);
	return (buf);
}

void	file_read(t_data *data, char *path)
{
	int	m_fd;
	char	*r_file;

	if (!data || !path)
		exit_error("Error: Somthing went wrong!\n");
	m_fd = open(path, O_RDONLY);
	if (m_fd < 0)
		exit_error("Error: can't open the map!\n");
	r_file = get_file_content(m_fd);
	if (!r_file)
		exit_error("Error: can't read the map!\n");
	data->file_data = ft_split(r_file, '\n');
	if (!data->file_data)
		exit_error("Erro: splitting issue\n");
}

void	parse(t_data *data, char *path)
{
	if (!path)
		exit_error("Error: Somthing went wrong!\n");
	path_parse(path);
	file_read(data, path);
	element_parse(data);
	// map_parse(); # you may make it last step in element_parse() function!
	// txtr_parse();
}
