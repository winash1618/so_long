#include "so_long.h"

void free_double_str(char **str)
{
   int i;

  i = 0;
  while (str[i])
  {
    printf("%s\n", str[i]);
    free(str[i]);
    i++;
  }
  if (str)
    free(str);
}

int parse_exit(t_game *game)
{
  int i;

  i = 0;
  while (game->map->map[i])
  {
    free(game->map->map[i]);
    i++;
  }
  if (game->map->map)
    free(game->map->map);
  game_exit(game);
  return (0);
}

void game_exit(t_game *game)
{
  if (game->map)
    free(game->map);
  if (game->img)
    free(game->img);
  mlx_destroy_image(game->mlx->mlx, game->pic[PLAYER]->img);
  mlx_destroy_image(game->mlx->mlx, game->pic[EXIT]->img);
  mlx_destroy_image(game->mlx->mlx, game->pic[COIN]->img);
  mlx_destroy_image(game->mlx->mlx, game->pic[FLOOR]->img);
  mlx_destroy_image(game->mlx->mlx, game->pic[WALL]->img);
  mlx_clear_window(game->mlx->mlx, game->mlx->win);
  mlx_destroy_window(game->mlx->mlx, game->mlx->win);
  if (game->mlx)
    free(game->mlx);
  free(game->pic[PLAYER]);
  free(game->pic[EXIT]);
  free(game->pic[COIN]);
  free(game->pic[FLOOR]);
  free(game->pic[WALL]);
  if (game)
    free(game);
  exit(0);
}