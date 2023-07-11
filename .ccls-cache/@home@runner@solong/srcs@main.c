#include "so_long.h"

void free_exit(t_game *game)
{
  (void) game;
  // if (game->map)
  //   free(game->map);
  // if (game->mlx)
  //   free(game->mlx);
  // if (game->img)
  //   free(game->img);
  // if (game)
  //   free(game);
  // exit(0);
}
void test(t_game *game)
{
  game->map->map[0] = "bi";
}

void init_game(t_game *game, char *file)
{
  (void) file;
  game->map = (t_map *)malloc(sizeof(t_map));
  game->map->map = (char **) malloc(sizeof(char *));
  game->map->map[0] = "hi";
  game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
  game->img = (t_img *)malloc(sizeof(t_img));
  if (!game->map)
    free_exit(game);
}

int main(int argc, char **argv)
{
  (void) argv;
	t_game *game;

	if (argc != 2)
  {
	  printf("Wrong number of arguments!!!\n");
    printf("Usage: ./so_long maps/map1.ber\n");
    return (0);
  }
  game = (t_game *)malloc(sizeof(t_game));
  init_game(game, argv[1]);
  printf("%s\n", game->map->map[0]);
  test(game);
  printf("%s\n", game->map->map[0]);
	game->mlx->mlx = mlx_init();
	game->mlx->win = mlx_new_window(game->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	mlx_loop(game->mlx->mlx);
	return (0);
}