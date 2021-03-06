/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amiguez <amiguez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 11:28:07 by amiguez           #+#    #+#             */
/*   Updated: 2022/06/03 14:39:22 by amiguez          ###   ########.fr       */
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
		ft_error("usage: ./so_long map_file\n", NULL, NULL);
	if (ft_ber(argv[1]) == 0)
		ft_error("error: map_file is not a .ber file\n", NULL, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("error: map not found\n", NULL, NULL);
	line = get_next_line(fd);
	if (line == NULL)
		ft_error("error: map empty\n", NULL, NULL);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1')
			ft_error("error: map not valid\n", line, NULL);
		i++;
	}
	game->info.x = i;
	game->info.map = ft_strdup(line);
	free(line);
	game->move = 0;
	ft_parsec2(game, fd, argv);
}

void	ft_parsec2(t_long *game, int fd, char **argv)
{
	int		full_wall;
	char	*line;

	line = get_next_line(fd);
	game->info.y = 1;
	while (line)
	{
		full_wall = is_full_wall(line);
		if (ft_has_wall(line, game->info.x) == 1)
			ft_error("error: map not valid\n", line, NULL);
		game->info.map = ft_str_malloc_join(&game->info.map, &line);
		line = get_next_line(fd);
		game->info.y++;
	}
	if (full_wall == 0)
		ft_error("error: map not valid\n", game->info.map, NULL);
	close(fd);
	if (ft_content_map(game) == 1)
		ft_error("error: map not valid (wrong content)\n", game->info.map, NULL);
	game->info.name = ft_strjoin("save/", argv[1]);
	if (game->info.name == NULL)
		ft_error("error\n", game->info.map, game->info.name);
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_error("error: mlx init\n", game->info.map, game->info.name);
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

int	ft_content_map(t_long *game)
{
	int		i;
	t_count	count;

	i = 0;
	count.p = 0;
	count.e = 0;
	count.c = 0;
	while (game->info.map[i])
	{
		if (game->info.map[i] == 'C')
			count.c++;
		if (game->info.map[i] == 'P')
			count.p++;
		if (game->info.map[i] == 'E')
			count.e++;
		i++;
	}
	game->ecp.c = count.c;
	if (count.c == 0 || count.p != 1 || count.e == 0)
		return (1);
	return (0);
}

int	is_full_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
