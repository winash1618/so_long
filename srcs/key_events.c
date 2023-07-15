#include "so_long.h"

static void game_end(t_game *game,int flag)
{
  if (flag)
    printf("You won in %d moves\n", game->player.move);
  parse_exit(game);
}

static void move_player(t_game *game, int x, int y)
{
  if (game->map->map[x][y] != '1')
  {
    printf("hi i am here\n");
    if (game->map->map[x][y] == 'C')
      game->player.collect += 1;
    else if (game->map->map[x][y] == 'E')
      game_end(game, 1);
    game->player.move += 1;
    game->map->map[x][y] = 'P';
    game->map->map[game->player.x][game->player.y] = '0';
    game->player.x = x;
    game->player.y = y;
  }
}

void render_image(t_game *game)
{
  for(int i = 0; i < game->map->height; i++)
  {
    for(int j = 0; j < game->map->width; j++)
    {
      if (game->map->map[i][j] == 'P')
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[PLAYER]->img, j * 48, i * 48);
      else if (game->map->map[i][j] == 'E')
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[EXIT]->img, j * 48, i * 48);
      else if (game->map->map[i][j] == 'C')
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[COIN]->img, j * 48, i * 48);
      else if (game->map->map[i][j] == '1')
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[WALL]->img, j * 48, i * 48);
      else if (game->map->map[i][j] == '0')
        mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->pic[FLOOR]->img, j * 48, i * 48);
    }
  }
}

int	event_handler(int keycode, t_game *game)
{
  printf("player location: x = %d, y = %d\n", game->player.x, game->player.y);
	if (keycode == A_KEY)
    move_player(game, game->player.x, game->player.y - 1);
  else if (keycode == D_KEY)
    move_player(game, game->player.x, game->player.y + 1);
	else if (keycode == W_KEY)
    move_player(game, game->player.x - 1, game->player.y);
  else if (keycode == S_KEY)
    move_player(game, game->player.x + 1, game->player.y);
	else if (keycode == ESC_KEY)
		game_end(game, 0);
  mlx_clear_window(game->mlx->mlx, game->mlx->win);
  render_image(game);
	return (0);
}