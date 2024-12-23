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