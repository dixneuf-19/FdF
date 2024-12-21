#include "fdf.h"

#include <stdio.h>


// int main()
// {
// 	void *mlx_ptr = mlx_init();
// 	void *win_ptr = mlx_new_window(mlx_ptr, 500, 500, "window");
// 	void *img_ptr = mlx_new_image(mlx_ptr, 500, 500);
// 	t_data data;
// 	data.data_addr = mlx_get_data_addr(img_ptr, &data.bpx, &data.sl, &data.e);
// 	printf("data addr %p\n", data.data_addr);
// 	printf("bits per pixel %d\n", data.bpx);
// 	printf("size line %d\n", data.sl);
// 	printf("endian %d\n", data.e);
// 	for (int i = 0; i < (500 * 500 * 4); i++)
// 	{
// 		data.data_addr[i] = -1;
// 		//printf("%d\n", i);
// 	}
// 	write(1, "done filling image", 19);
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
// 	while (1)
// 	{
// 	}
// }

// static void	free_all(char **splits)
// {
// 	while (*splits)
// 	{
// 		free(*splits);
// 		splits++;
// 	}
// 	free(splits);
// }

