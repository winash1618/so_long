#include "so_long.h"

char *str_modify_safe(char *line)
{
  char *temp;

  temp = line;
  line = ft_strtrim(line, "\n");
  free(temp);
  return (line);
}

void get_map_dimension(t_game *game, int fd)
{
  t_map *map = game->map;
  char *line;
  int i;

  i = 0;
  if (get_next_line(fd, &line) > 0)
    i++;
  line = str_modify_safe(line);
  map->width = ft_strlen(line);
  if (check_line_for_map_errors(line, map->width) == -1)
    game_exit(game);
  free(line);
  while (get_next_line(fd, &line) > 0)
	{
    line = str_modify_safe(line);
    if (check_line_for_map_errors(line, map->width) == -1)
      game_exit(game);
		free(line);
    i++;
	}
  map->height = i;
}

void find_player(t_game *game)
{
  int i;
  int j;
  char **map;

  map = game->map->map;
  i = 0;
  j = 0;
  while(map[i])
  {
    j = 0;
    while (map[i][j])
    {
      if (map[i][j] == 'P')
      {
        game->player.x = i;
        game->player.y = j;
      }
      j++;
    }  
    i++;
  }
}

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

void parse_map(t_game *game, int fd)
{
  game->map->map = (char **)malloc(sizeof(char *) * (game->map->height + 1));
  char *line;
  int i;

  i = 0;
  while (get_next_line(fd, &line) > 0)
	{
    game->map->map[i] = str_modify_safe(line);
    i++;
	}
  game->map->map[i] = NULL;
  check_map_validity(game);
  find_player(game);
  printf("player_x : %d, player_y : %d\n", game->player.x, game->player.y);
  check_valid_path(game);
}