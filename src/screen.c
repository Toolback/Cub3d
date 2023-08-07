/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:17:35 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 20:17:37 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_ray(t_data *data)
{
	double	angle;
	double	dist;

	angle = ((double)data->ray.i - (data->win.x / 2)) * 33 / (data->win.x / 2);
	angle = angle * M_PI / 180;
	data->ray.x = data->dir.x * cos(angle) - data->dir.y * sin(angle);
	data->ray.y = data->dir.y * cos(angle) + data->dir.x * sin(angle);
	dist = hypot(data->ray.x, data->ray.y);
	data->ray.x /= dist;
	data->ray.y /= dist;
}

void	ft_dir(t_data *data)
{
	if (data->ray.x >= 0)
		data->ray.v = 1;
	else
		data->ray.v = 0;
	if (data->ray.y >= 0)
		data->ray.w = 1;
	else
		data->ray.w = 0;
}

void	ft_ver(t_data *data)
{
	double	x;
	double	y;

	x = floor(data->pos.x) + data->ray.v;
	y = data->pos.y + (x - data->pos.x) * (data->ray.y / data->ray.x);
	while ((int)floor(y) > 0 && (int)floor(y) < data->map.y)
	{
		if (data->map.tab[(int)floor(y)][(int)(x - 1 + data->ray.v)] == '1')
		{
			data->hit.x = x;
			data->hit.y = y;
			data->hit.d = hypot(x - data->pos.x, y - data->pos.y);
			return ;
		}
		x += (2 * data->ray.v - 1);
		y += (2 * data->ray.v - 1) * data->ray.y / data->ray.x;
	}
	data->hit.x = data->pos.x;
	data->hit.y = data->pos.y;
	data->hit.d = 1000000000;
}

void	ft_hor(t_data *data)
{
	double	y;
	double	x;

	y = floor(data->pos.y) + data->ray.w;
	x = data->pos.x + (y - data->pos.y) * (data->ray.x / data->ray.y);
	while ((int)floor(x) > 0 && (int)floor(x) < data->map.x)
	{
		if (data->map.tab[(int)(y - 1 + data->ray.w)][(int)floor(x)] == '1')
		{
			if (data->hit.d > hypot(x - data->pos.x, y - data->pos.y))
			{
				data->hit.x = x;
				data->hit.y = y;
				data->hit.d = hypot(x - data->pos.x, y - data->pos.y);
			}
			return ;
		}
		y += (2 * data->ray.w - 1);
		x += (2 * data->ray.w - 1) * data->ray.x / data->ray.y;
	}
}

void	ft_screen(t_data *data)
{
	int		bpp;
	int		sl;
	int		end;

	data->img.ptr = mlx_new_image(data->mlx.ptr, data->win.x, data->win.y);
	data->img.adr = (unsigned int *)mlx_get_data_addr(data->img.ptr, &bpp, &sl, &end);
	data->stk = malloc(sizeof(t_stk) * data->win.x);
	while (data->ray.i < data->win.x)
	{
		ft_ray(data);
		ft_dir(data);
		ft_ver(data);
		ft_hor(data);
		ft_stock(data);
		ft_column(data, ft_size(data));
		data->ray.i++;
	}
	ft_sprite(data);
}