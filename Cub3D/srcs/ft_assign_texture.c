/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:18:27 by ahkalama          #+#    #+#             */
/*   Updated: 2024/02/26 15:58:49 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_assign_aspect(t_data *data, t_img *img, char *sp)
{
	img->img = mlx_xpm_file_to_image(data->mlx.ptr,
			sp, &img->width, &img->height);
	if (!img->img)
		return (printf("Error. Invalid texture path : [%s].\n", sp), 0);
	img->get_addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->steps);
	return (1);
}

static int	ft_assign_color(int *color, char **sp)
{
	char	**rgb;
	int		rgb_val[3];

	rgb = ft_split(sp[1], ',');
	if (!rgb)
		return (printf("Error. Malloc failed.\n"), 0);
	if (ft_matrix_len((void **)rgb) != 3)
		return (printf("Error. Invalid color format [%s].\n", sp[1]), 0);
	if (!ft_is_number(rgb[0]) || !ft_is_number(rgb[1]) || !ft_is_number(rgb[2]))
		return (printf("Error. Invalid color values [%s].\n", sp[1]), 0);
	rgb_val[0] = ft_atoi(rgb[0]);
	rgb_val[1] = ft_atoi(rgb[1]);
	rgb_val[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void **)rgb);
	if (rgb_val[0] < 0 || rgb_val[0] > 255 || rgb_val[1] < 0 || rgb_val[1] > 255
		|| rgb_val[2] < 0 || rgb_val[2] > 255)
		return (printf("Error. Invalid color values [%s].\n", sp[1]), 0);
	*color = ft_create_color(0, rgb_val[0], rgb_val[1], rgb_val[2]);
	return (1);
}

int	ft_assign_texture(t_data *data, char **sp)
{
	if (ft_strcmp(sp[0], "NO") == 0)
		return (ft_assign_aspect(data, &data->map.north, sp[1]));
	else if (ft_strcmp(sp[0], "SO") == 0)
		return (ft_assign_aspect(data, &data->map.south, sp[1]));
	else if (ft_strcmp(sp[0], "WE") == 0)
		return (ft_assign_aspect(data, &data->map.west, sp[1]));
	else if (ft_strcmp(sp[0], "EA") == 0)
		return (ft_assign_aspect(data, &data->map.east, sp[1]));
	else if (ft_strcmp(sp[0], "F") == 0)
		return (ft_assign_color(&data->map.floor_c, sp));
	else if (ft_strcmp(sp[0], "C") == 0)
		return (ft_assign_color(&data->map.ceiling_c, sp));
	return (printf("Error. Invalid texture information [%s].\n", sp[0]), 0);
}
