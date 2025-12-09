/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:39:29 by abmasnao          #+#    #+#             */
/*   Updated: 2025/12/09 13:25:08 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define T	0
# define R	1
# define G	2
# define B	3
# define ROT_SPEED 0.020
# define MOVE_SPEED 0.07

# define NO	0
# define SO	1
# define WE	2
# define EA	3
# define F	4
# define C	5

# define WIDTH 1080
# define HEIGHT 720

# define RIGHT	65363
# define LEFT	65361

# define CROSS_BUTTON 17

# define ESC 65307
# define A 97
# define S 115
# define D 100
# define W 119

# define INVALID_CHARACTER "Error: invalid character in the map! \" 01NSEW\"\n"

typedef struct s_utils
{
	int		elmnts[6];
	char	**rbgs;
	int		i_rbg[4];
	char	**copy;
	int		map_height;
	int		map_width;
	char	**file_data;
	int		pos[2];
}				t_utils;

typedef struct s_image
{
	void	*img_ptr;
	char	*img_data;
	char	*img_path;
	int		height;
	int		width;
	int		bpp;
	int		size_line;
	int		endian;
}			t_image;

typedef struct s_raycasting_data
{
	double			cam_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			side_x;
	double			side_y;
	double			delta_x;
	double			p_w_d;
	double			delta_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wallx;
	int				tex_x;
	int				tex_y;
	double			step;
	double			texpos;
	t_image			*tex;
	int				bpp_bytes;
	char			*src;
	unsigned int	color;
}	t_raycasting_data;

typedef struct s_keys
{
	int	a;
	int	d;
	int	w;
	int	s;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	t_image	image;
	t_image	no;
	t_image	so;
	t_image	we;
	t_image	ea;

	int		f;
	int		c;

	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	void	*mlx_ptr;
	void	*window;

	char	**map;

	t_utils	utils;
	t_keys	keys;
}				t_data;

typedef struct s_mem_t
{
	void			*ptr;
	struct s_mem_t	*next;
}				t_mem_t;

//cub_lib
void	exit_error(char *msg);
void	ft_exit(int exit_status);
void	ft_free(void);
void	mlx_free(t_data *data);
t_data	**get_data_ptr(void);
void	set_data_ptr(t_data *data);
bool	ft_isspace(char c);
void	*ft_malloc(size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	add_to_gc(void *ptr);
t_mem_t	**get_collector(void);
void	*ft_realloc(char *old_ptr, size_t new_size);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *s1);
size_t	ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char *s, unsigned int start, size_t len);
bool	is_in(char *str, char *set);
bool	valid_char_name(char c);

// parsing_utils
void	elmnts_init(int *arr);
int		mo_wspaces(char *line);
bool	is_valid_element(char *line);
int		corr_size(char *line, int size);
int		count_elements(char **line, int end);

bool	is_map_begin(char *line);
size_t	map_len(char **data, int index);
int		get_max_row(char **map, int index);
int		map_1st_line_index(char **data);
bool	much(char c, char *set);

void	map_in_the_file(t_data *data);
void	copy_map(t_data *data);
void	characters_helper(t_data *data, int spcl_char, int i, int j);

void	comma_num(char *line);
void	valid_chars(t_data *data, char *value);
void	rgb_only(char *line);
void	size_three(t_data *data);

size_t	rgb_len(char *value, int offset);
int		num_len(char *str);
int		a_to_rgb_i(char *str);

bool	corr_elmnt(char *elmnt);
int		get_line_index(char **data, char *elmnt);
bool	extension_check(char *path);
char	*parse_value(char *value);
char	*get_element_value(t_data *data, char *elmnt);

// parsing
void	element_parse(t_data *data);
void	map_process(t_data *data);
void	parse(t_data *data, char *path);
void	rgb_parse(t_data *data);
void	textures_parse(t_data *data);

// raycasting
void	raycasting(t_data *data);
void	init_data(t_data *data);

#endif