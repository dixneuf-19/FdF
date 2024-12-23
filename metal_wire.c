/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_wire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:26:13 by mzary             #+#    #+#             */
/*   Updated: 2024/12/23 02:45:52 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal_wire.h"

int	main(int argc, char **argv)
{
	void	*pointers[3];
	t_input	input;
	t_image	image;

	if (argc != 2)
		exit_failure(1);
	input.path = argv[1];
	parse_input(&input);
	draw_image(&image, &input, pointers);
	show_result(pointers);
}

void	exit_failure(int error)
{
	if (error == 1)
		ft_putendl_fd(ARGS_NUM, STDERR_FILENO);
	else if (error == 2)
		ft_putendl_fd(NULL_PTR, STDERR_FILENO);
	else if (error == 3)
		ft_putendl_fd(FILE_ERR, STDERR_FILENO);
	else if (error == 4)
		ft_putendl_fd(INIT_MLX, STDERR_FILENO);
	else if (error == 5)
		ft_putendl_fd(NULL_IMG, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_matrix(t_point **m, int lines_num)
{
	while (lines_num)
	{
		free(m[lines_num - 1]);
		lines_num -= 1;
	}
	free(m);
}

void	destroy_mlx(void **pointers, int n)
{
	
}
