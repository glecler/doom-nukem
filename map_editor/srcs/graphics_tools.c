#include "../includes/doom_editor.h"

int     ft_big_pixel_img(char *addr, t_node node, unsigned char *rgb, t_e_data *e_data)
{
	int x_buff;
	int y_buff;

	x_buff = node.x - 10;
	y_buff = node.y - 10;
	while (x_buff < node.x + 10)
	{
		while (y_buff < node.y + 10)
		{
			y_buff++;
			ft_put_pixel_img(addr, x_buff, (y_buff - node.z) *
				e_data->win_data->size_line, rgb);
		}
		y_buff = node.y - 10;
		x_buff++;
	}
	return (0);
}

void	ft_flush_img(char **addr)
{
	int i;

	i = -1;
	while (++i < 3200000)
		(*addr)[i] = 0;
}

int		ft_put_pixel_img(char *addr, int x, int y, unsigned char *rgb)
{
	char	*cpy;

	cpy = addr;
	if (x > 1000 || y > 3200000 || x < 0 || y < 42)
		return (0);
	addr += y + x * 4;
	*(addr) = rgb[0];
	*(addr + 1) = rgb[1];
	*(addr + 2) = rgb[2];
	addr = cpy;
	return (1);
}

void    ft_put_line_vert(t_node a, t_node b, char *addr, t_e_data *data)
{
	double y;
	double x;
	double coeff;

	coeff = 0;
	y = 0;
	x = a.x;
	if (a.y - a.z > b.y - b.z)
		ft_coord_swap(&a, &b);
	if (b.y - b.z != a.y - a.z)
		coeff = (b.x - a.x) / (b.y - b.z - a.y + a.z);
	while (a.y + y  - a.z <= b.y - b.z)
	{
		x = ceil(y * coeff) + a.x;
		ft_put_pixel_img(addr, x, (a.y - a.z + y) *
			data->win_data->size_line, data->win_data->rgb);
		ft_put_pixel_img(addr, x + 1, (a.y - a.z +  y) *
			data->win_data->size_line, data->win_data->rgb);
		y += 1;
	}
}

void    ft_put_line_img(t_node a, t_node b, char *addr, t_e_data *data)
{
	double	coeff;
	double	x;
	double		y;
	int		res;

	y = a.y - a.z;
	x = 0;
	coeff = 0;
	if (b.x < a.x)
		ft_coord_swap(&a, &b);
	if (b.x != a.x)
		coeff = (b.y - b.z - a.y + a.z) / (b.x - a.x);
	if (b.x == a.x || fabs(coeff) > 1)
		ft_put_line_vert(a, b, addr, data);
	while ((a.x + x <= b.x) && fabs(coeff) <= 1)
	{
		y = ceil(x * coeff) + a.y - a.z;
		res = ft_put_pixel_img(addr, a.x + x, y *
			data->win_data->size_line, data->win_data->rgb);
		res = ft_put_pixel_img(addr, a.x + x, (y + 1) *
			data->win_data->size_line, data->win_data->rgb);
		x += 1;
	}
}