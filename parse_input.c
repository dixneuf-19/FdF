/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:26:16 by mzary             #+#    #+#             */
/*   Updated: 2024/12/23 02:43:35 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal_wire.h"

static void	extract_line(t_point **m, int line_num, char *line, int line_size);
static void	count_sizes(t_input *input);
static int	count_width(char *line);

void	parse_input(t_input *input)
{
	int		y;
	int		fd;
	char	*line;

	count_sizes(input);
	fd = open(input->path, O_RDONLY);
	if (fd == -1)
		exit_failure(3);
	input->m = (t_point **)malloc(sizeof(t_point *) * input->s_y);
	if (!input->m)
		exit_failure(2);
	y = 1;
	while (y <= input->s_y)
	{
		line = get_next_line(fd);
		extract_line(input->m, y, line, input->s_x);
		free(line);
		y += 1;
	}
	close(fd);
}

static void	extract_line(t_point **m, int line_num, char *line, int line_size)
{
	char	**line_split;
	int		x;

	m[line_num - 1] = (t_point *)malloc(sizeof(t_point) * line_size);
	if (!m[line_num - 1])
	{
		free_matrix(m, line_num - 1);
		free(line);
		exit_failure(2);
	}
	line_split = ft_split(line, ' ');
	if (!line_split)
	{
		free_matrix(m, line_num);
		free(line);
		exit_failure(2);
	}
	x = 0;
	while (line_split[x])
	{
		m[line_num - 1][x].alt = ft_atoi(line_split[x]);
		free(line_split[x]);
		x += 1;
	}
	free(line_split);
}

static void	count_sizes(t_input *input)
{
	int		fd;
	char	*line;

	input->s_y = 0;
	input->s_x = 0;
	fd = open(input->path, O_RDONLY);
	if (fd == -1)
		exit_failure(3);
	line = get_next_line(fd);
	while (line)
	{
		if (input->s_x == 0)
			input->s_x = count_width(line);
		input->s_y += 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static int	count_width(char *line)
{
	int		size_x;
	char	**line_splits;

	size_x = 0;
	line_splits = ft_split(line, ' ');
	if (!line_splits)
	{
		free(line);
		exit_failure(2);
	}
	while (line_splits[size_x])
	{
		free(line_splits[size_x]);
		size_x += 1;
	}
	free(line_splits);
	return (size_x);
}
