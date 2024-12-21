/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_wire.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:26:13 by mzary             #+#    #+#             */
/*   Updated: 2024/12/21 04:50:06 by mzary            ###   ########.fr       */
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
	print_result(pointers);
}

void	exit_failure(int error)
{
	if (error == 1)
		ft_putendl_fd(ARGS_NUM, STDERR_FILENO);
	else if (error == 2)
		ft_putendl_fd(NULL_PTR, STDERR_FILENO);
	else if (error == 3)
		ft_putendl_fd(FILE_ERR, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	free_memory(t_input *input, void **pointers, int n)
{
	
}
