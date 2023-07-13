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