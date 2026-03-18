/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:47:42 by mthamir           #+#    #+#             */
/*   Updated: 2024/06/19 17:13:34 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (game->map_l[i])
	{
		free(game->map_l[i]);
		i++;
	}
	free(game->map_l);
	game->map_l = NULL;
	exit(0);
}

void	render_images(t_game *game, int i, int j)
{
	int	x;
	int	y;

	x = j * 50;
	y = i * 50;
	if (game->map_l[i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall, x, y);
	if (game->map_l[i][j] != '1')
		mlx_put_image_to_window(game->mlx, game->win, game->b_g, x, y);
	if (game->map_l[i][j] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->coin, x, y);
	if (game->map_l[i][j] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player, x, y);
	if (game->map_l[i][j] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit, x, y);
}

void	creat_window(t_game *game)
{
	int	i;
	int	j;

	i = game->width * 50;
	j = game->hight * 50;
	game->mlx = mlx_init();
	if (!game->mlx)
		error_handling(game, "initialization mlx fails\n");
	game->win = mlx_new_window(game->mlx, i, j, game->prg_name);
	if (!game->win)
		error_handling(game, "creating new window fails\n");
	init_images(game);
	i = 0;
	while (game->map_l[i])
	{
		j = 0;
		while (game->map_l[i][j])
		{
			render_images(game, i, j);
			j++;
		}
		i++;
	}
	mlx_hook(game->win, 17, 0, x_click, game);
	mlx_hook(game->win, 2, 1L << 0, move, game);
	mlx_loop(game->mlx);
}

void	check_for_screen_resolution(t_game *game)
{
	if ((game->hight * 50) > 1400)
		error_handling(game, "map is too big for the screen\n");
	if ((game->width * 50) > 2550)
		error_handling(game, "map is too big for the screen\n");
}

void	initial_var(t_game *game)
{
	game->win = NULL;
	game->mlx = NULL;
	game->player = NULL;
	game->wall = NULL;
	game->b_g = NULL;
	game->coin = NULL;
	game->exit = NULL;
	game->player_path = NULL;
	game->wall_path = NULL;
	game->coint_path = NULL;
	game->b_g_path = NULL;
	game->exit_path = NULL;
	game->f_name = NULL;
	game->map_l = NULL;
	game->p = 0;
	game->c = 0;
	game->e = 0;
}
