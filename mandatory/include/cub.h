/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:39:29 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 10:14:02 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


# define WIDTH 1080
# define HEIGHT 720

# define CROSS_BUTTON 17

# define ESC 27
# define W 119
# define A 97
# define S 115
# define D 100

// structs

typedef struct s_data
{
	void	*mlx_ptr;
	void	*window;
	
}				t_data;

typedef struct s_mem_t
{
	void	*ptr;
	struct s_mem_t	*next;
}				t_mem_t;


// tools

t_mem_t	**get_collector(void);
size_t	ft_strlen(char *str);
void	exit_error(char *msg);
void	*ft_malloc(size_t size);
void	ft_free(void);
void	ft_exit(int	exit_status);

#endif