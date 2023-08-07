/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 14:32:20 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 20:25:51 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int		ft_line(t_data *data, char *line)
{
	int		i;

	i = 0;
	skipspace(line, &i);
	if ((line[i] == '1' || data->err.m == 1) && line[i] != '\0')
		data->err.n = ft_map(data, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		data->err.n = ft_res(data, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		data->err.n = ft_texture(data, &data->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		data->err.n = ft_texture(data, &data->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		data->err.n = ft_texture(data, &data->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		data->err.n = ft_texture(data, &data->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		data->err.n = ft_texture(data, &data->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		data->err.n = ft_colors(&data->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		data->err.n = ft_colors(&data->tex.c, line, &i);
	if (skipspace(line, &i) && data->err.n == 0 && line[i] != '\0')
		return (ft_strerror(-10));
	return (data->err.n < 0 ? ft_strerror(data->err.n) : 0);
}

int		parse_map(t_data *data, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(data, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	ft_pos(data);
	// data->spr = NULL;
	ft_slist(data);
	return (ft_parcheck(data));
}