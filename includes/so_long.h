#ifndef SO_LONG_H
# define SO_LONG_H
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/includes/libft.h"
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct s_map
{
	int     width;
	int     height;
	char    **map;
}               t_map;

typedef struct s_img
{
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     width;
	int     height;
}               t_img;

typedef struct s_player
{
	int     x;
	int     y;
	int     move; // Number of steps player moved
	int     collect; // Number of collectible collected
}          t_player;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
}          t_mlx;

typedef struct s_game
{
	t_map       *map;
	t_img       *img;
  t_mlx       *mlx;
	t_player    player;
}              t_game;



#endif