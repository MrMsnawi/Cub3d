/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:39:29 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/11 19:41:01 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>


# define WIDTH 1080
# define HEIGHT 720

// arrows
# define UP		65362
# define DOWN	65364
# define RIGHT	65363
# define LEFT	65361

// cross button event
# define CROSS_BUTTON 17

// esc + asdw keys
# define ESC 65307
# define A 97
# define S 115
# define D 100
# define W 119

// structs

typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	char	*img_path;
	int		height;
	int		widtht;
	int		bpp;
	int		size_line;
	int		endian;
}			t_image;

typedef struct s_data
{
	t_image	image;
	t_image	no;
	t_image	so;
	t_image	we;
	t_image	ea;

	int	f;
	int	c;

	void	*mlx_ptr;
	void	*window;

	char	**file_data;
	int		elmnts[6];
}				t_data;

typedef struct s_mem_t
{
	void	*ptr;
	struct s_mem_t	*next;
}				t_mem_t;

// parsing
void	parse(t_data *data, char *path);
void	element_parse(t_data *data);
int		mo_wspaces(char *line);
void	textures_parse(t_data *data);
bool	ft_isspace(char c);
char	*get_element_value(t_data *data, char *elmnt);

// tools
t_mem_t	**get_collector(void);
size_t	ft_strlen(char *str);
void	exit_error(char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void);
void	ft_exit(int	exit_status);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif