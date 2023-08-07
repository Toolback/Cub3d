#include "../include/cub3d.h"


int		ft_close(t_data *data, int win)
{
	int	i;

	i = 0;
	while (i < data->map.y)
		free(data->map.tab[i++]);
	free(data->map.tab);
	free(data->tex.n);
	free(data->tex.s);
	free(data->tex.e);
	free(data->tex.w);
	free(data->tex.i);
	if (win == 1)
		mlx_destroy_window(data->mlx.ptr, data->win.ptr);
	free(data->mlx.ptr);
	exit(0);
	return (1);
}

void	ft_move(t_data *data, double c)
{
	data->pos.x += c * (data->dir.x * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
		data->pos.x -= c * (data->dir.x * SPEED / 100);
	data->pos.y += c * (data->dir.y * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
		data->pos.y -= c * (data->dir.y * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '2')
	{
		data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] = '0';
		data->map.spr--;
		ft_slist(data);
	}
}

void	ft_strafe(t_data *data, double c)
{
	data->pos.x -= c * (data->dir.y * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
		data->pos.x += c * (data->dir.y * SPEED / 100);
	data->pos.y += c * (data->dir.x * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '1')
		data->pos.y -= c * (data->dir.x * SPEED / 100);
	if (data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] == '2')
	{
		data->map.tab[(int)floor(data->pos.y)][(int)floor(data->pos.x)] = '0';
		data->map.spr--;
		ft_slist(data);
	}
}

void	ft_rotate(t_data *data, double c)
{
	double	dist;

	data->dir.x = data->dir.x * cos(c * TURN) - data->dir.y * sin(c * TURN);
	data->dir.y = data->dir.y * cos(c * TURN) + data->dir.x * sin(c * TURN);
	dist = hypot(data->dir.x, data->dir.y);
	data->dir.x /= dist;
	data->dir.y /= dist;
}

int		ft_key(int key, void *arg)
{
	if (key == ESC)
		ft_close(arg, 1);
	else if (key == W)
		ft_move(arg, 1);
	else if (key == A)
		ft_strafe(arg, -1);
	else if (key == S)
		ft_move(arg, -1);
	else if (key == D)
		ft_strafe(arg, 1);
	else if (key == LEFT)
		ft_rotate(arg, -1);
	else if (key == RIGHT)
		ft_rotate(arg, 1);
	ft_draw(arg);
	return (1);
}