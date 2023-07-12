#include "so_long.h"

void parse_exit(t_game *game)
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
}
void game_exit(t_game *game)
{
  if (game->map)
    free(game->map);
  if (game->mlx)
    free(game->mlx);
  if (game->img)
    free(game->img);
  if (game)
    free(game);
  exit(0);
}