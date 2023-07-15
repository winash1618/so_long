#include "so_long.h"

char **str_duplicate_map(t_game *game, char **map)
{
  char **new_map;
  int i;

  new_map = (char **)malloc(sizeof(char *) * (game->map->height + 1));
  i = 0;
  printf("New Map\n");
  while (map[i])
  {
    new_map[i] = ft_strdup(map[i]);
    printf("%s\n", new_map[i]);
    i++;
  }
  new_map[i] = NULL;
  return (new_map);
}

int valid_path_finder_algorithm(t_game *game, char **map, int x, int y)
{
  int i;

  i = 0;
  if (map[x][y] == 'E')
    return (1);
  printf("map value: %c %d %d \n", map[x][y], x, y);
  map[x][y] = '1';
  if (map[x + 1][y] != '1' && i != 1)
    i = valid_path_finder_algorithm(game, map, x + 1, y);
  if (map[x][y + 1] != '1' && i != 1)
    i = valid_path_finder_algorithm(game, map, x, y + 1);
  if (map[x - 1][y] != '1' && i != 1)
    i = valid_path_finder_algorithm(game, map, x - 1, y);
  if (map[x][y - 1] != '1' && i != 1)
    i = valid_path_finder_algorithm(game, map, x , y - 1);
  if (i == 1)
    return (1);
  else
    return (-1);
}

void check_valid_path(t_game *game)
{
  char **map;

  map = str_duplicate_map(game, game->map->map);
  if (valid_path_finder_algorithm(game, map, game->player.x, game->player.y) == -1)
  {
    printf("Path not found\n");
    free_double_str(map);
    parse_exit(game);
  }
  free_double_str(map);
}