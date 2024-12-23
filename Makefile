all:
	cc *.c libft/*/*.c libmlx.a -lX11 -lXext -o metal_wire
fclean:
	rm -rf metal_wire