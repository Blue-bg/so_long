/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:28:07 by amiguez           #+#    #+#             */
/*   Updated: 2022/04/25 17:24:02 by amiguez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

//open a return a malloc char ** of the map
void	ft_parsec(int argc, char **argv, t_long *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if (argc != 2)
		ft_error("usage: ./so_long map_file\n", NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("error: map not found\n", NULL);
	line = get_next_line(fd);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			ft_error("error: map not valid 1(no wall on the top\n)", line);
		i++;
	}
	game -> info_map.size_x = i;
	game -> info_map.map = ft_strdup(line);
	free(line);
	ft_parsec2(game, fd);
}

void	ft_parsec2(t_long *game, int fd)
{
	int		full_wall;
	char	*line;

	full_wall = 0;
	line = get_next_line(fd);
	game -> info_map.size_y = 1;
	while (line)
	{
		if (ft_has_wall(line, game -> info_map.size_x) == 1)
			ft_error("error: map not valid (not closed side/dif len)\n", line);
		game -> info_map.map = ft_str_malloc_join(&game -> info_map.map, &line);
		line = get_next_line(fd);
		game -> info_map.size_y++;
	}
	if (full_wall == 1)
		ft_error("error: map not valid (No wall on the bottom)\n", NULL);
	close(fd);
	if (ft_content_map(*game) == 1)
		ft_error("error: map not valid (wrong content)\n", NULL);
}

int	ft_has_wall(char *line, int len)
{
	int	i;

	i = 0;
	if (line[i] != '1')
		return (1);
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'C'
			&& line[i] != 'P' && line[i] != 'E')
			return (1);
		i++;
	}
	if (line[i - 1] != '1')
		return (1);
	if ((ft_strlen(line) != len + 1 && line[i] == '\n')
		|| (ft_strlen(line) != len && line[i] != '\n'))
		return (1);
	return (0);
}

int	ft_content_map(t_long game)
{
	int		i;
	t_count	count;

	i = 0;
	count.p = 0;
	count.e = 0;
	count.c = 0;
	while (game.info_map.map[i])
	{
		if (game.info_map.map[i] == 'C')
			count.c++;
		if (game.info_map.map[i] == 'P')
			count.p++;
		if (game.info_map.map[i] == 'E')
			count.e++;
		i++;
	}
	if (count.c == 0 || count.p == 0 || count.e == 0)
		return (1);
	return (0);
}
