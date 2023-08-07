/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurenaul <jurenaul@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:19:57 by jurenaul          #+#    #+#             */
/*   Updated: 2023/08/07 20:19:57 by jurenaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// # include "../lib/libft/include/libft.h"
# include "../lib/minilibx-linux/mlx.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>


# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define SPEED 15
# define TURN 0.05


# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
	int				fsh;
}				t_img;

typedef struct	s_err
{
	int				n;
	int				m;
	int				p;
}				t_err;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				spr;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	*i;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct	s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			v;
	double			w;
}				t_ray;

typedef struct	s_hit
{
	double			x;
	double			y;
	double			d;
}				t_hit;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			d;
}				t_spr;

typedef struct	s_stk
{
	double			x;
	double			y;
	double			d;
}				t_stk;

typedef struct s_data
{
    t_mlx           mlx;
    t_win           win;
    t_img           img;
    t_err           err;
    t_map           map;
    t_tex           tex;
    t_pos           pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
	t_spr			*spr;
    t_stk           *stk;
}               t_data;
// main.c
void ft_draw(t_data *data);

//utils.c
int		skipspace(char *line, int *i);
int     namecheck(char *arg, char *ext);
int		ft_strerror(int err);
int		ft_atoi(char *line, int *i);
char	*error(char *stock);

// parsing.c
int		ft_line(t_data *data, char *line);
int		parse_map(t_data *data, char *cub);

// parsing_map.c
int		ft_xpm(t_data *data, unsigned int **adr, char *file);
int		ft_texture(t_data *data, unsigned int **adr, char *line, int *i);
int		ft_slablen(t_data *data, char *line);
char	*ft_slab(t_data *data, char *line, int *i);
int		ft_map(t_data *data, char *line, int *i);

// parsing_tools.c
int		ft_res(t_data *data, char *line, int *i);
int		ft_colors(unsigned int *color, char *line, int *i);
void	ft_pos(t_data *data);
int		ft_slist(t_data *data);
// parsing_check.c
int		ft_mapcheck(t_data *data);
int		ft_parcheck(t_data *data);

// screen.c
void	ft_screen(t_data *data);

// screen_utils.c
void			ft_stock(t_data *data);
int				ft_size(t_data *data);
void			ft_column(t_data *data, int size);
unsigned int	ft_pixel(t_data *data, double i);

// sprite.c 
void			ft_sprite(t_data *data);

// key.c
int		ft_key(int key, void *arg);
void	ft_rotate(t_data *data, double c);
void	ft_strafe(t_data *data, double c);
void	ft_move(t_data *data, double c);
int		ft_close(t_data *data, int win);

// gnl.c
int		get_next_line(int fd, char **line);

#endif