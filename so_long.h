/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 05:43:57 by amiguez           #+#    #+#             */
/*   Updated: 2022/04/27 17:22:04 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h" // libft
# include "minilibx_opengl_20191021/mlx.h" // mlx
# include <math.h> // al math fonction
# include <stdio.h> // perror and strerror
# include <stdlib.h> // exit , malloc , free
# include <fcntl.h> // open , close
# include <unistd.h> // write , read

typedef struct s_map
{
	char	*map;
	int		x;
	int		y;
}			t_map;

typedef struct s_long
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	t_map	info;

}			t_long;

typedef struct s_count
{
	int		e;
	int		c;
	int		p;
}			t_count;

// *************************** //

// *************************** //

//      main.c       //

int		main(int argc, char **argv);
void	ft_error(char *str, void *dump);

//     parsec.c      //

void	ft_parsec(int argc, char **argv, t_long *game);
void	ft_parsec2(t_long *game, int fd);
int		ft_has_wall(char *line, int len);
int		ft_content_map(t_long game);

//     reader.c      //

void	ft_render_windows(t_long game);

// *************************** //
// ********* debug.c ********* //

void	print_map(t_map info);
void	debug(int index, t_long game);

// *************************** //
#endif