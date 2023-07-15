#include "so_long.h"

int check_line_for_unknown_characters(char *line)
{
  while (*line)
  {
    if (!(*line == '1' || *line  == '0' || *line == 'P' || *line == 'E' || *line == 'C'))
      return (-1);
    line++;
  }
  return (1);
}

int check_line_for_map_errors(char *line, size_t width)
{
  if (check_line_for_unknown_characters(line) == -1)
  {
    printf("Map Error1\n");
    free(line);
    return (-1);
  }
  if (ft_strlen(line) != width)
  {
    printf("Map Error2\n");
    free(line);
    return(-1);
  }
  return (1);
}

char *str_modify_safe(char *line)
{
  char *temp;

  temp = line;
  line = ft_strtrim(line, "\n");
  free(temp);
  return (line);
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
  check_valid_path(game);
}