/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmasnao <abmasnao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:46:58 by abmasnao          #+#    #+#             */
/*   Updated: 2025/09/13 17:47:13 by abmasnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

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
