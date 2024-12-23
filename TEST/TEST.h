/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:56:58 by mzary             #+#    #+#             */
/*   Updated: 2024/12/23 03:04:49 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft/lib/libft.h"
# include "libft/gnl/get_next_line.h"
# include "libft/mlx/mlx.h"

# define ARGS_NUM	"invalid arguments number"
# define NULL_PTR	"error allocating memory"
# define FILE_ERR	"error reading from file"
# define INIT_MLX	"error initiating session"
# define NULL_IMG	"error creating the image"

# define SCALE	106
# define PI 	3.1416
# define PAD	15
// PAD ≃ SCALE * (1 - cos(PI/4)) / 2
# define DIAG	75
// DIAG ≃ SCALE / sqrt(2)
# define MAG	3

typedef struct s_point
{
	int			alt;
	char		*img_addr;
}				t_point;

typedef struct s_input
{
	char		*path;
	int			s_x;
	int			s_y;
	t_point		**m;
}				t_input;

typedef struct s_image
{
	char		*base_addr;
	int			side;
	int			bpx;
	int			sl;
	int			e;
}				t_image;

void	exit_failure(int error);
void	free_matrix(t_point **m, int lines_num);
void	destroy_mlx(void **pointers, int n);

void	parse_input(t_input *input);
void	draw_image(t_image *image, t_input *input, void **pointers);
void	show_result(void **pointers);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buff
{
	char			content[BUFFER_SIZE];
	ssize_t			length;
	char			end;
	struct s_buff	*next;
}				t_buff;

char	*get_next_line(int fd);

void	link_check_buff(t_buff *p_plus, t_buff *p_buff);
char	*return_line(t_buff *p_plus);
void	free_buff(t_buff *p_plus);


#endif
