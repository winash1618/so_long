#include "so_long.h"

void init_images(t_game *game)
{
  game->pic[PLAYER]->img = mlx_xpm_file_to_image(game->mlx->mlx, \
                          "./textures/player.xpm", &game->pic[PLAYER]->width, \
                          &game->pic[PLAYER]->height);
  game->pic[EXIT]->img = mlx_xpm_file_to_image(game->mlx->mlx, \
                          "./textures/exit.xpm", &game->pic[EXIT]->width, \
                          &game->pic[EXIT]->height);
  game->pic[COIN]->img = mlx_xpm_file_to_image(game->mlx->mlx, \
                          "./textures/coin.xpm", &game->pic[COIN]->width, \
                          &game->pic[COIN]->height);
  game->pic[FLOOR]->img = mlx_xpm_file_to_image(game->mlx->mlx, \
                          "./textures/floor.xpm", &game->pic[FLOOR]->width, \
                          &game->pic[FLOOR]->height);
  game->pic[WALL]->img = mlx_xpm_file_to_image(game->mlx->mlx, \
                          "./textures/wall.xpm", &game->pic[WALL]->width, \
                          &game->pic[WALL]->height);
}

void render_image(t_game *game)
{
  for(int i = 0; i < game->map->height; i++)
  {
    for(int j = 0; j < game->map->width; j++)
    {
      if (game->map->map[i][j] == 'P')
      {
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[PLAYER]->img, j * 48, i * 48);
      }
      else if (game->map->map[i][j] == 'E')
      {
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[EXIT]->img, j * 48, i * 48);
      }
      else if (game->map->map[i][j] == 'C')
      {
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[COIN]->img, j * 48, i * 48);
      }
      else if (game->map->map[i][j] == '1')
      {
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[WALL]->img, j * 48, i * 48);
      }
      else if (game->map->map[i][j] == '0')
      {
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[FLOOR]->img, j * 48, i * 48);
      }
    }
  }
  // mlx_destroy_image(game->mlx->mlx, game->img->img);
  // sleep(3);
  // mlx_clear_window(game->mlx->mlx, game->mlx->win);
}

void init_game(t_game *game, char *file) {
  int fd;

  fd = open(file, O_RDONLY);
  if (fd < 0)
    return;
  game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
  game->img = (t_img *)malloc(sizeof(t_img));
  game->map = (t_map *)malloc(sizeof(t_map));
  game->pic[PLAYER] = (t_img *)malloc(sizeof(t_img));
  game->pic[EXIT] = (t_img *)malloc(sizeof(t_img));
  game->pic[COIN] = (t_img *)malloc(sizeof(t_img));
  game->pic[FLOOR] = (t_img *)malloc(sizeof(t_img));
  game->pic[WALL] = (t_img *)malloc(sizeof(t_img));
  get_map_dimension(game, fd);
  close(fd);
  fd = open(file, O_RDONLY);
  if (fd < 0)
    return;
  parse_map(game, fd);
  close(fd);
  printf("game->map->map[0] : %s\n", game->map->map[0]);
}

int	event_handler(int keycode, t_game *game)
{
	// key_event_updown(keycode, img);
	// key_event_rightleft(keycode, img);
	// key_event_rotate(keycode, img);
  printf("HI I AM");
  fflush(stdout);
	if (keycode == ESC_KEY)
		parse_exit(game);
  if (keycode == W_KEY)
  {
    game->map->map[game->player.x][game->player.y] = 'C';
  }
  mlx_clear_window(game->mlx->mlx, game->mlx->win);
  render_image(game);
	return (0);
}

int main(int argc, char **argv) {
  t_game *game;

  if (argc != 2) {
    printf("Wrong number of arguments!!!\n");
    printf("Usage: ./so_long maps/map1.ber\n");
    return (0);
  }
  game = (t_game *)malloc(sizeof(t_game));
  init_game(game, argv[1]);
  game->mlx->mlx = mlx_init();
  game->mlx->win =
  mlx_new_window(game->mlx->mlx, 48 * game->map->width, 48 * game->map->height, "so_long");
  init_images(game);
  render_image(game);
  mlx_hook(game->mlx->win, 2, 1L << 0, event_handler, game); // it's different in linux (1L << 0)
	mlx_hook(game->mlx->win, 17, 0, parse_exit, game);
  mlx_loop(game->mlx->mlx);
  parse_exit(game);
  return (0);
}