#ifndef FDF_PUT_LINE_H
# define FDF_PUT_LINE_H

void	put_line_left_side(void *mlx, void *win, t_seg line, t_point d);
void	put_line_right_side(void *mlx, void *win, t_seg line, t_point d);
void	octant_1(void *mlx, void *win, t_seg line);
void	octant_2(void *mlx, void *win, t_seg line);
void	octant_3(void *mlx, void *win, t_seg line);
void	octant_4(void *mlx, void *win, t_seg line);
void	octant_5(void *mlx, void *win, t_seg line);
void	octant_6(void *mlx, void *win, t_seg line);
void	octant_7(void *mlx, void *win, t_seg line);
void	octant_8(void *mlx, void *win, t_seg line);
void	octant_limit(void *mlx, void *win, t_seg line);

#endif
