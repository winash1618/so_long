 #include "so_long.h"

void free_exit(t_game *game)
{
  (void) game;
  if (game->map->map)
    free(game->map->map);
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

int check_line_for_unknown_characters(char *line)
{
  while (*line)
  {
    if (*line == '\n')
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

int get_map_dimension(t_map *map, int fd)
{
  (void)map;
   
  char *line;
  int i;

  i = 0;
  if (get_next_line(fd, &line) > 0)
    i++;
  // free(line);
  line = str_modify_safe(line);
  map->width = ft_strlen(line);
  if (check_line_for_map_errors(line, map->width) == -1)
      return (-1);
  free(line);
  while (get_next_line(fd, &line) > 0)
	{
    line = str_modify_safe(line);
    if (check_line_for_map_errors(line, map->width) == -1)
      return (-1);
		free(line);
    i++;
	}
  map->height = i;
  return (1);
}

int parse_map(t_map *map, int fd)
{
  if (get_map_dimension(map, fd) == -1)
    return (-1);
  
  printf("map height = %d, map width = %d\n", map->height, map->width);
  map->map = (char **)malloc(sizeof(char *));
  return (1);
}

void init_game(t_game *game, char *file)
{
  int fd;
  
  fd = open(file, O_RDONLY);
  if (fd < 0)
		return ;
  game->map = (t_map *)malloc(sizeof(t_map));
  if (parse_map(game->map, fd) == -1)
    free_exit(game);
  // printf("%s \n", game->map->map[0]);
  game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
  game->img = (t_img *)malloc(sizeof(t_img));
  if (!game->map)
    free_exit(game);
}

int main(int argc, char **argv)
{
  (void) argv;
	t_game *game;

	if (argc != 2)
  {
	  printf("Wrong number of arguments!!!\n");
    printf("Usage: ./so_long maps/map1.ber\n");
    return (0);
  }
  game = (t_game *)malloc(sizeof(t_game));
  init_game(game, argv[1]);
  // printf("%s\n", game->map->map[0]);
  // printf("%s\n", game->map->map[0]);
	// game->mlx->mlx = mlx_init();
	// game->mlx->win = mlx_new_window(game->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	// mlx_loop(game->mlx->mlx);
  free_exit(game);
	return (0);
}