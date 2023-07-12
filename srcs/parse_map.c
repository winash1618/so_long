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
}