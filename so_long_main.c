/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:17:51 by mthamir           #+#    #+#             */
/*   Updated: 2024/06/19 16:52:36 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_lines(t_game	*game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (*game).hight)
	{
		(*game).map_l[i] = get_next_line((*game).fd);
		if ((*game).map_l[i] == NULL)
			error_handling(game, "allocation fails\n");
		if ((*game).map_l[i][j] == '\n' || (*game).map_l[i][j] == '\0')
			error_handling(game, "invalid map\n");
		remove_new_line(game, i);
		i++;
	}
	game->map_l[game->hight] = NULL;
}

void	go_pars(t_game	*game)
{
	int	i;

	i = 0;
	get_lines(game);
	check_other_char(game);
	if (!(*game).map_l || !(*game).map_l[i])
		error_handling(game, "invalid map\n");
	check_len_lines(game);
	check_walls(game);
	check_if_rectangular(game);
	if (count_p_c_e(game, 0, 0))
		error_handling(game, "invalid map\n");
	game->f_m = fake_map(*game);
	if (!check_the_path_for_coins((*game).x_p, (*game).y_p, game, game->f_m))
		error_handling(game, "path to coins not valid\n");
	game->f_m = fake_map(*game);
	if (!check_the_path_for_exit((*game).x_p, (*game).y_p, game, game->f_m))
		error_handling(game, "path to Exit not valid\n");
	check_for_screen_resolution(game);
}

int	get_num_of_lines(t_game *game)
{
	int		i;
	int		fd;
	char	*n;

	i = 0;
	n = NULL;
	fd = open((*game).f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("%s\n", strerror(errno));
		exit(1);
	}
	while (1)
	{
		n = get_next_line(fd);
		if (!n)
			break ;
		if (*n == '\n')
			error_handling(game, "invalid map\n");
		free(n);
		n = NULL;
		i++;
	}
	close(fd);
	return (i);
}

void	check_map_extention(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	while (filename[i] != '.' && i > 0)
		i--;
	filename = &filename[i];
	if (ft_strcmpr(filename, ".ber"))
	{
		ft_printf("file extension is not valid\nvalid file: filename.ber\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_printf("usage: ./a.out filename.ber\n"), 1);
	check_map_extention(av[1]);
	game.prg_name = av[0];
	initial_var(&game);
	game.f_name = av[1];
	game.hight = get_num_of_lines(&game);
	game.map_l = malloc ((game.hight + 1) * sizeof(char *));
	if (!game.map_l)
		return (write (2, strerror(errno), ft_strlen(strerror(errno))));
	game.fd = open(game.f_name, O_RDONLY);
	if (game.fd == -1)
	{
		ft_printf("%s\n", strerror(errno));
		exit(1);
	}
	go_pars(&game);
	creat_window(&game);
	close(game.fd);
	return (0);
}
