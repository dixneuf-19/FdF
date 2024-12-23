/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:26:19 by mzary             #+#    #+#             */
/*   Updated: 2024/12/23 03:01:55 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal_wire.h"

static void	calculate_address(t_image *image, t_input *input, void *mlx_ptr);
static void	fill_image(t_image *image, t_input *input, void *mlx_ptr);
static void	trace_line(t_point A, t_point B, t_image *image, void *mlx_ptr);

void	draw_image(t_image *image, t_input *input, void **pointers)
{
	pointers[0] = mlx_init();
	if (!pointers[0])
	{
		free_matrix(input->m, input->s_y);
		exit_failure(4);
	}
	image->side = SCALE * (input->s_x + input->s_y);
	pointers[1] = mlx_new_image(pointers[0], image->side, image->side);
	if (!pointers[1])
	{
		free_matrix(input->m, input->s_y);
		exit_failure(5);
	}
	mlx_get_data_addr(pointers[1], &image->bpx, &image->sl, &image->e);
	fill_image(image, input, pointers[0]);
}

static void	fill_image(t_image *image, t_input *input, void *mlx_ptr)
{
	t_point	**m;
	int		y;
	int		x;

	calculate_address(image, input, mlx_ptr);
	m = input->m;
	y = 0;
	while (y < input->s_y)
	{
		x = 0;
		while (x < input->s_x)
		{
			if (y != input->s_y - 1 && x != input->s_x - 1)
			{
				trace_line(m[y][x], m[y][x + 1], image, mlx_ptr);
				trace_line(m[y][x], m[y + 1][x], image, mlx_ptr);
			}
			else if (x != input->s_x - 1)
				trace_line(m[y][x], m[y][x + 1], image, mlx_ptr);
			else if (y != input->s_y - 1)
				trace_line(m[y][x], m[y + 1][x], image, mlx_ptr);
			x += 1;
		}
		y += 1;
	}
}

static void	calculate_address(t_image *img, t_input *inp, void *mlx_ptr)
{
	int		y;
	int		x;
	char	*addr;

	y = 0;
	while (y < inp->s_y)
	{
		x = 0;
		while (x < inp->s_x)
		{
			addr = img->base_addr + PAD * (inp->s_x + inp->s_y) * img->sl;
			addr += SCALE * inp->s_y * img->bpx / 8;
			addr += DIAG * (x + y) * img->sl;
			addr += DIAG * (x - y) * img->bpx / 8;
			addr -= MAG * inp->m[y][x].alt * img->sl;
			inp->m[y][x].img_addr = addr;
			// remove
			*(unsigned int *)addr = mlx_get_color_value(mlx_ptr, 0xffffffff);
			x += 1;
		}
		y += 1;
	}
}

static void	trace_line(t_point A, t_point B, t_image *image, void *mlx_ptr)
{

}