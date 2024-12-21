/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_wire.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:56:58 by mzary             #+#    #+#             */
/*   Updated: 2024/12/21 05:15:01 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METAL_WIRE_H
# define METAL_WIRE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
// # include <math.h>
# include "libft/lib/libft.h"
# include "libft/gnl/get_next_line.h"
# include "libft/mlx/mlx.h"

# define ARGS_NUM	"invalid number of args"
# define NULL_PTR	"null pointer returned"
# define FILE_ERR	"error reading from file"

typedef struct s_input
{
	char		*path;
	int			size_x;
	int			size_y;
	int			**matrix;
}				t_input;

typedef struct s_image
{
	char		*addr;
	int			width;
	int			height;
	int			bpx;
	int			size_line;
	int			endian;
}				t_image;

void	exit_failure(int error);
void	free_memory(t_input *input, void **pointers, int n);
void	free_matrix(int **matrix, int lines_num);

void	parse_input(t_input *input);
void	draw_image(t_image *image, t_input *input, void *pointers);
void	print_result(void *pointers);

#endif
