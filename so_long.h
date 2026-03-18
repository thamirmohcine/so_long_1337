/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:22:56 by mthamir           #+#    #+#             */
/*   Updated: 2024/06/19 17:18:34 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <mlx.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifdef __linux__
#  define KEY_ESC 65307
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_RIGHT 65363
#  define KEY_LEFT 65361
#  define KEY_ESC_ALT 9
#  define KEY_UP_ALT 111
#  define KEY_DOWN_ALT 116
#  define KEY_RIGHT_ALT 114
#  define KEY_LEFT_ALT 113
# else
#  define KEY_ESC 53
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_RIGHT 124
#  define KEY_LEFT 123
#  define KEY_ESC_ALT 53
#  define KEY_UP_ALT 126
#  define KEY_DOWN_ALT 125
#  define KEY_RIGHT_ALT 124
#  define KEY_LEFT_ALT 123
# endif

typedef struct s_game
{
	void	*win;
	void	*mlx;
	void	*player;
	void	*wall;
	void	*b_g;
	void	*coin;
	void	*exit;
	char	**f_m;
	void	*player_path;
	void	*wall_path;
	void	*coint_path;
	void	*b_g_path;
	void	*exit_path;
	char	*f_name;
	char	*prg_name;
	char	**map_l;
	int		hight;
	int		width;
	int		fd;
	int		c;
	int		c0;
	int		e;
	int		p;
	int		x_p;
	int		y_p;
	int		moves;
}			t_game;

int		error_handling(t_game *game, char *er_type);
void	check_other_char(t_game	*game);
void	check_len_lines(t_game	*game);
int		check_walls(t_game *game);
void	check_if_rectangular(t_game *game);
int		is_one(char c);
void	ft_free(char **s, int i);
char	**fake_map(t_game game);
int		check_the_path_for_coins(int x, int y, t_game *game, char **matrix);
int		check_the_path_for_exit(int x, int y, t_game *game, char **matrix);
int		count_p_c_e(t_game	*game, int i, int j);
int		ft_strcmpr(char *s1, char *s2);
int		check_all_1(char *s);
int		check_first_and_last(char c);
void	remove_new_line(t_game	*game, int i);
int		direction(t_game *game, int x, int y);
int		move(int key, t_game *game);
int		x_click(t_game *game);
int		ft_loop(t_game *game);
void	init_images(t_game *game);
void	free_map(t_game *game);
void	render_images(t_game *game, int i, int j);
void	creat_window(t_game *game);
void	get_lines(t_game	*game);
void	initial_var(t_game *game);
void	check_for_screen_resolution(t_game *game);
void	go_pars(t_game	*game);
int		get_num_of_lines(t_game *game);
void	check_map_extention(char *filename);
/* for get_next_line */
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *s);
char	*ft_copy(char *s1, char *s2, int i);
char	*ft_strjoin(char	*s1, char	*s2);
int		check_for_nl(char	**buff);
char	*get_next_line(int fd);
/* for ft_printf */
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putint(int nbr);
int		ft_printf(const char *format, ...);

#endif