#include "so_long.h"

void init_images(t_game *game) {
  game->pic[PLAYER]->img = mlx_xpm_file_to_image(
      game->mlx->mlx, "./textures/player.xpm", &game->pic[PLAYER]->width,
      &game->pic[PLAYER]->height);
  game->pic[PLAYER]->addr = (char(*))mlx_get_data_addr(
      game->pic[PLAYER]->img, &game->pic[PLAYER]->bits_per_pixel,
      &game->pic[PLAYER]->line_length, &game->pic[PLAYER]->endian);
  game->pic[EXIT]->img =
      mlx_xpm_file_to_image(game->mlx->mlx, "./textures/exit.xpm",
                            &game->pic[EXIT]->width, &game->pic[EXIT]->height);
  game->pic[EXIT]->addr = (char(*))mlx_get_data_addr(
      game->pic[EXIT]->img, &game->pic[EXIT]->bits_per_pixel,
      &game->pic[EXIT]->line_length, &game->pic[EXIT]->endian);
  game->pic[COIN]->img = mlx_xpm_file_to_image(
      game->mlx->mlx, "./textures/coin.xpm", &game->pic[COIN]->width,
      &game->pic[COIN]->height);
  game->pic[COIN]->addr = (char(*))mlx_get_data_addr(
      game->pic[COIN]->img, &game->pic[COIN]->bits_per_pixel,
      &game->pic[COIN]->line_length, &game->pic[COIN]->endian);
  game->pic[FLOOR]->img = mlx_xpm_file_to_image(
      game->mlx->mlx, "./textures/floor.xpm", &game->pic[FLOOR]->width,
      &game->pic[FLOOR]->height);
  game->pic[FLOOR]->addr = (char(*))mlx_get_data_addr(
      game->pic[FLOOR]->img, &game->pic[FLOOR]->bits_per_pixel,
      &game->pic[FLOOR]->line_length, &game->pic[FLOOR]->endian);
  game->pic[WALL]->img =
      mlx_xpm_file_to_image(game->mlx->mlx, "./textures/wall.xpm",
                            &game->pic[WALL]->width, &game->pic[WALL]->height);
  game->pic[WALL]->addr = (char(*))mlx_get_data_addr(
      game->pic[WALL]->img, &game->pic[WALL]->bits_per_pixel, &game->pic[WALL]->line_length,
      &game->pic[WALL]->endian);
}

void render_image(t_game *game)
{
  mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[EXIT]->img, 200, 200);
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
      mlx_new_window(game->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
  init_images(game);
  render_image(game);
  mlx_loop(game->mlx->mlx);
  parse_exit(game);
  return (0);
}