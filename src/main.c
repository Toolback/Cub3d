/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:19:08 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 20:19:08 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void ft_draw(t_data *data)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	data->ray = ray;
	data->hit = hit;
	ft_screen(data);
	mlx_put_image_to_window(data->mlx.ptr, data->win.ptr, data->img.ptr, 0, 0);
	free(data->img.ptr);
	free(data->img.adr);
}

int		launch_game(t_data *data, char *map)
{
	t_pos	pos;
	t_dir	dir;

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	data->pos = pos;
	data->dir = dir;
	data->mlx.ptr = mlx_init();
	if (parse_map(data, map) == -1)
		return (ft_close(data, 0));
	// if (bmp == 1)
	// 	return (ft_bitmap(data));
	ft_rotate(data, 1);
	ft_move(data, 1);
	ft_rotate(data, -1);
	ft_move(data, -1);
	data->win.ptr = mlx_new_window(data->mlx.ptr, data->win.x, data->win.y, "cub3D");
	ft_draw(data);
	mlx_hook(data->win.ptr, 2, 0, ft_key, data);
	mlx_hook(data->win.ptr, 17, 0, ft_close, data);
	mlx_loop(data->mlx.ptr);
	return (1);
}

void init_2(t_data *data)
{
	t_map	map;
	t_tex	tex;
	t_spr	*spr;
	t_stk	*stk;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	spr = NULL;
	stk = NULL;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	tex.c = NONE;
	tex.f = NONE;
	data->map = map;
	data->tex = tex;
	data->spr = spr;
	data->stk = stk;
}

void init_data(t_data *data)
{
	// SCOPE/POINTER ISSUE ?
	t_mlx	mlx;
	t_win	win;
	t_img	img;
	t_err	err;

	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	win.x = 0;
	win.y = 0;
	img.fsh = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	data->mlx = mlx;
	data->win = win;
	data->img = img;
	data->err = err;
	init_2(data);
}

int main(int ac, char **av)
{
    t_data *data;
	data = (t_data *)malloc(sizeof(t_data));

	if (ac == 2 && namecheck(av[1], "cub"))
    {
		// parse_map(data, av[1]); WIP
        init_data(data);
		launch_game(data, av[1]);
    }
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}