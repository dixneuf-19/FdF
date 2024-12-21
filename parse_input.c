/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:26:16 by mzary             #+#    #+#             */
/*   Updated: 2024/12/21 05:31:20 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal_wire.h"

static void	count_size(t_input *input);
static int	count_width(char *line);
static void	extract_line(int **matrix, int line_num, char *line, int line_size);

void	parse_input(t_input *input)
{
	int		**matrix;
	int		y;
	int		fd;
	char	*line;

	count_size(input);
	fd = open(input->path, O_RDONLY);
	if (fd == -1)
		exit_failure(3);
	matrix = (int **)malloc(sizeof(int *) * input->size_y);
	if (!matrix)
		exit_failure(2);
	y = 1;
	while (y <= input->size_y)
	{
		line = get_next_line(fd);
		extract_line(matrix, y, line, input->size_x);
		free(line);
		y += 1;
	}
	close(fd);
}

static void	extract_line(int **matrix, int line_num, char *line, int line_size)
{
	char	**line_split;
	int		x;

	matrix[line_num - 1] = (int *)malloc(sizeof(int) * line_size);
	if (!matrix[line_num - 1])
	{
		free_matrix(matrix, line_num - 1);
		free(line);
		exit_failure(2);
	}
	line_split = ft_split(line, ' ');
	if (!line_split)
	{
		free_matrix(matrix, line_num);
		free(line);
		exit_failure(2);
	}
	x = 0;
	while (line_split[x])
	{
		matrix[line_num - 1][x] = ft_atoi(line_split[x]);
		free(line_split[x]);
		x += 1;
	}
	free(line_split);
}

void	free_matrix(int **matrix, int lines_num)
{
	int	line;

	line = 1;
	while (line <= lines_num)
	{
		free(matrix[line - 1]);
		line += 1;
	}
	free(matrix);
}

static void	count_size(t_input *input)
{
	int		fd;
	char	*line;

	input->size_y = 0;
	input->size_x = 0;
	fd = open(input->path, O_RDONLY);
	if (fd == -1)
		exit_failure(3);
	line = get_next_line(fd);
	while (line)
	{
		if (input->size_x == 0)
			input->size_x = count_width(line);
		input->size_y += 1;
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
		free(line_splits[size_x++]);
	free(line_splits);
	return (size_x);
}
