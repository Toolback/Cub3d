/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:25:04 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 23:02:40 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_xpm(t_data *data, unsigned int **adr, char *file)
{
	int		fd;
	void	*img;
	int		tab[5];

	if (namecheck(file, "xpm") == 0)
		return (-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(data->mlx.ptr, file, &tab[0], &tab[1]);
	if (img == NULL || tab[0] != 64 || tab[1] != 64)
		return (-1);
	*adr = (unsigned int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	free(img);
	return (0);
}

int		ft_texture(t_data *data, unsigned int **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (-7);
	(*i) += 2;
	skipspace(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = ft_xpm(data, adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

int		ft_slablen(t_data *data, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
			count++;
		else if (line[i] == 'E')
			count++;
		i++;
	}
	if (data->map.x != 0 && data->map.x != count)
		return (-1);
	return (count);
}

char	*ft_slab(t_data *data, char *line, int *i)
{
	char	*datalab;
	int		j;

	if (!(datalab = malloc(sizeof(char) * (ft_slablen(data, line) + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			datalab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			datalab[j++] = line[*i];
			data->map.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(datalab);
			return (NULL);
		}
		(*i)++;
	}
	datalab[j] = '\0';
	return (datalab);
}

int		ft_map(t_data *data, char *line, int *i)
{
	char	**tmp;
	int		j;

	data->err.m = 1;
	if (!(tmp = malloc(sizeof(char *) * (data->map.y + 2))))
		return (-11);
	j = -1;
	while (++j < data->map.y)
		tmp[j] = data->map.tab[j];
	if ((tmp[data->map.y] = ft_slab(data, line, i)) == NULL)
	{
		free(tmp);
		return (-12);
	}
	tmp[data->map.y + 1] = NULL;
	if (data->map.y > 0)
		free(data->map.tab);
	data->map.tab = tmp;
	data->map.y++;
	if ((data->map.x = ft_slablen(data, line)) == -1)
		return (-13);
	return (0);
}
