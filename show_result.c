/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_result.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzary <mzary@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:29:45 by mzary             #+#    #+#             */
/*   Updated: 2024/12/23 02:46:36 by mzary            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "metal_wire.h"

void	show_result(void **pointers)
{
	//create new window
	//attach hooks to window
	//put image to window
	//handle leaks and errors
	mlx_put_image_to_window(pointers[0], pointers[1], pointers[2], 0, 0);
	while (1)
		pause();
}
