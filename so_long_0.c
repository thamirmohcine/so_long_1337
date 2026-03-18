/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:16:55 by mthamir           #+#    #+#             */
/*   Updated: 2024/06/19 16:50:46 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fix_sprite_black_bg(t_game *game, void *sprite)
{
	char			*spr_addr;
	char			*bg_addr;
	int			spr_bpp;
	int			bg_bpp;
	int			spr_sl;
	int			bg_sl;
	int			spr_endian;
	int			bg_endian;
	int			x;
	int			y;
	unsigned int	*spr_px;
	unsigned int	*bg_px;

	spr_addr = mlx_get_data_addr(sprite, &spr_bpp, &spr_sl, &spr_endian);
	bg_addr = mlx_get_data_addr(game->b_g, &bg_bpp, &bg_sl, &bg_endian);
	if (!spr_addr || !bg_addr || spr_bpp < 24 || bg_bpp < 24)
		return ;
	y = 0;
	while (y < 50)
	{
		x = 0;
		while (x < 50)
		{
			spr_px = (unsigned int *)(spr_addr + (y * spr_sl) + (x * (spr_bpp / 8)));
			bg_px = (unsigned int *)(bg_addr + (y * bg_sl) + (x * (bg_bpp / 8)));
			if (((*spr_px) & 0x00FFFFFF) == 0)
				*spr_px = *bg_px;
			x++;
		}
		y++;
	}
}

int	direction(t_game *game, int x, int y)
{
	int	i;
	int	j;

	if (game->map_l[y][x] == '1' || (game->map_l[y][x] == 'E' && game->c0 != 0))
		return (1);
	if (game->map_l[y][x] == 'C')
		game->c0--;
	if (game->map_l[y][x] == 'E' && game->c0 == 0)
		free_map(game);
	game->map_l[y][x] = 'P';
	game->map_l[game->y_p][game->x_p] = '0';
	game->x_p = x;
	game->y_p = y;
	game->moves++;
	mlx_clear_window(game->mlx, game->win);
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
	ft_printf("moves number : %d\n", game->moves);
	return (0);
}

int	move(int key, t_game *game)
{
	if (key == KEY_ESC || key == KEY_ESC_ALT)
		free_map(game);
	else if (key == KEY_UP || key == KEY_UP_ALT)
		direction(game, game->x_p, (game->y_p - 1));
	else if (key == KEY_DOWN || key == KEY_DOWN_ALT)
		direction(game, game->x_p, (game->y_p + 1));
	else if (key == KEY_RIGHT || key == KEY_RIGHT_ALT)
		direction(game, (game->x_p + 1), game->y_p);
	else if (key == KEY_LEFT || key == KEY_LEFT_ALT)
		direction(game, (game->x_p - 1), game->y_p);
	return (0);
}

int	x_click(t_game *game)
{
	free_map(game);
	return (0);
}

int	ft_loop(t_game *game)
{
	mlx_hook(game->win, 17, 0, x_click, game);
	mlx_hook(game->win, 2, 1L << 0, move, game);
	return (0);
}

void	init_images(t_game *game)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	game->player = mlx_xpm_file_to_image(game->mlx, "./textures/p.xpm", &a, &b);
	if (!game->player)
		error_handling(game, "invalid image\n");
	game->b_g = mlx_xpm_file_to_image(game->mlx, "./textures/g.xpm", &a, &b);
	if (!game->b_g)
		error_handling(game, "invalid image\n");
	game->exit = mlx_xpm_file_to_image(game->mlx, "./textures/d.xpm", &a, &b);
	if (!game->exit)
		error_handling(game, "invalid image\n");
	game->coin = mlx_xpm_file_to_image(game->mlx, "./textures/c.xpm", &a, &b);
	if (!game->coin)
		error_handling(game, "invalid image\n");
	game->wall = mlx_xpm_file_to_image(game->mlx, "./textures/w.xpm", &a, &b);
	if (!game->wall)
		error_handling(game, "invalid image\n");
	fix_sprite_black_bg(game, game->player);
	fix_sprite_black_bg(game, game->coin);
	fix_sprite_black_bg(game, game->exit);
}
