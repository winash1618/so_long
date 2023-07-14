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

# ifdef linux
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define Q_KEY 81
#  define E_KEY 69
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define M_KEY 109
#  define H_KEY 104
#  define Q_KEY 81
#  define E_KEY 69
# endif

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
  t_img       *pic[5];
  t_mlx       *mlx;
	t_player    player;
}              t_game;

enum	e_type
{
	PLAYER,
  EXIT,
  COIN,
  FLOOR,
  WALL
};


char *str_modify_safe(char *line);
int parse_exit(t_game *game);
void game_exit(t_game *game);
int check_line_for_unknown_characters(char *line);
int check_line_for_map_errors(char *line, size_t width);
void get_map_dimension(t_game *game, int fd);
void parse_map(t_game *game, int fd);
void check_map_validity(t_game *game);
void free_double_str(char **str);


#endif