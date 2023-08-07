/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:17:21 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 23:00:15 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_res(t_data *data, char *line, int *i)
{
	if (data->win.x != 0 || data->win.y != 0)
		return (-3);
	(*i)++;
	data->win.x = ft_atoi(line, i);
	data->win.y = ft_atoi(line, i);
	if (data->win.x > 2560)
		data->win.x = 2560;
	if (data->win.y > 1400)
		data->win.y = 1400;
	skipspace(line, i);
	if (data->win.x <= 0 || data->win.y <= 0 || line[*i] != '\0')
		return (-4);
	return (0);
}

int		ft_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_atoi(line, i);
	(*i)++;
	g = ft_atoi(line, i);
	(*i)++;
	b = ft_atoi(line, i);
	skipspace(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

void	ft_pos(t_data *data)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < data->map.y)
	{
		while (++j < data->map.x)
		{
			c = data->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				data->pos.y = (double)i + 0.5;
				data->pos.x = (double)j + 0.5;
				data->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				data->dir.x *= (c == 'W') ? -1 : 1;
				data->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				data->dir.y *= (c == 'N') ? -1 : 1;
				data->err.p++;
			}
		}
		j = -1;
	}
}

int		ft_slist(t_data *data)
{
	int		i;
	int		j;
	int		k;

	if (data->spr != NULL)
		free(data->spr);
	if (!(data->spr = malloc(sizeof(t_spr) * data->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < data->map.y)
	{
		k = 0;
		while (k < data->map.x)
		{
			if (data->map.tab[j][k] == '2')
			{
				data->spr[i].y = (double)j + 0.5;
				data->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}
