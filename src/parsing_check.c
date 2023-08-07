/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 22:54:31 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 23:02:57 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_mapcheck(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < data->map.y)
	{
		j = 0;
		while (j < data->map.x)
		{
			if (data->map.tab[i][j] != '1' && i == 0)
				return (-1);
			else if (data->map.tab[i][j] != '1' && i == data->map.y - 1)
				return (-1);
			else if (data->map.tab[i][j] != '1' && j == 0)
				return (-1);
			else if (data->map.tab[i][j] != '1' && j == data->map.x - 1)
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int		ft_parcheck(t_data *data)
{
	if (data->win.x <= 0 || data->win.y <= 0)
		return (ft_strerror(-14));
	else if ((data->tex.n == NULL || data->tex.s == NULL || data->tex.e == NULL)
			|| (data->tex.w == NULL || data->tex.i == NULL))
		return (ft_strerror(-15));
	else if (data->tex.c == NONE || data->tex.f == NONE)
		return (ft_strerror(-16));
	else if (data->err.p == 0)
		return (ft_strerror(-17));
	else if (data->err.p > 1)
		return (ft_strerror(-18));
	else if (ft_mapcheck(data) == -1)
		return (ft_strerror(-19));
	return (1);
}
