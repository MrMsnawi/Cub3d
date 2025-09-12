/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:51:19 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/09 11:53:21 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

void	exit_error(char *msg)
{
	if (msg)
		write(2, msg, ft_strlen(msg));
	ft_exit(EXIT_FAILURE);
}
