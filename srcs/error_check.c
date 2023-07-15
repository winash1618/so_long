#include "so_long.h"

int count_element(char *line, char c)
{
  int i;
  int count;

  i = 0;
  count = 0;
  while (line[i])
  {
    if (line[i] == c)
      count++;
    i++; 
  }
  return (count);
}

void check_element_count_validity(t_game *game, int player_count, int exit_count, int collectible_count)
{
  if (player_count != 1)
  {
    printf("Map Error 3\n");
    parse_exit(game);
  }
  if (exit_count != 1)
  {
    printf("Map Error 4\n");
    parse_exit(game);
  }
  if (collectible_count == 0)
  {
    printf("Map Error 5\n");
    parse_exit(game);
  }
}

int check_map_top_and_bottom(t_map *map)
{
  int i;
  char *top;
  char *bottom;

  i = 0;
  top = map->map[0];
  bottom = map->map[map->height - 1];
  while (top[i])
  {
    if (top[i] == 1 || bottom[i] == 1)
    {
      printf("Map Error 6\n");
      return (-1);
    }
    i++; 
  }
  return (1);
}

void check_map_validity(t_game *game)
{
  char**  map;
  int     player_count;
  int     exit_count;
  int     collectible_count;
  int     i;

  map = game->map->map;
  i = 0;
  player_count = 0;
  exit_count = 0;
  collectible_count = 0;
  if (check_map_top_and_bottom(game->map) == -1)
    parse_exit(game);
  while (map[i])
  {
    if (!(map[i][0] == '1' && map[i][game->map->width - 1] == '1'))
    {
      printf("Map Error 7\n");
      parse_exit(game);
    }
    player_count += count_element(map[i], 'P');
    exit_count += count_element(map[i], 'E');
    collectible_count += count_element(map[i], 'C');
    i++;
  }
  check_element_count_validity(game, player_count, exit_count, collectible_count);
}