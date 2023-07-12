 #include "so_long.h"

void init_game(t_game *game, char *file)
{
  int fd;
  
  fd = open(file, O_RDONLY);
  if (fd < 0)
		return ;
  game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
  game->img = (t_img *)malloc(sizeof(t_img));
  game->map = (t_map *)malloc(sizeof(t_map));
  get_map_dimension(game, fd);
  close(fd);
  fd = open(file, O_RDONLY);
  if (fd < 0)
		return ;
  parse_map(game, fd);
  close(fd);
  printf("game->map->map[0] : %s\n", game->map->map[0]);
}

int main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
  {
	  printf("Wrong number of arguments!!!\n");
    printf("Usage: ./so_long maps/map1.ber\n");
    return (0);
  }
  game = (t_game *)malloc(sizeof(t_game));
  init_game(game, argv[1]);
	game->mlx->mlx = mlx_init();
	game->mlx->win = mlx_new_window(game->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	mlx_loop(game->mlx->mlx);
  parse_exit(game);
	return (0);
}