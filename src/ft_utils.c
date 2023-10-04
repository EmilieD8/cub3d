/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emiliedrouot <emiliedrouot@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:24:14 by mschaub           #+#    #+#             */
/*   Updated: 2023/09/23 01:23:08 by emiliedrouo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

size_t	ft_iscub(char *file)
{
	size_t	i;

	i = ft_strlen(file) - 1;
	if (file[i--] != 'b')
		return (0);
	if (file[i--] != 'u')
		return (0);
	if (file[i--] != 'c')
		return (0);
	return (1);
}

int	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
