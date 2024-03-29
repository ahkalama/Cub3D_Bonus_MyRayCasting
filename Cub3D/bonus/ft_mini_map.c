/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:28:02 by ahkalama          #+#    #+#             */
/*   Updated: 2024/02/26 16:19:23 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static t_mini_map	ft_fill_mini_map_comp(int x, int y, int radius)
{
	t_mini_map	mini_map;

	mini_map.x = x;
	mini_map.y = y;
	mini_map.radius = radius;
	return (mini_map);
}

int	ft_is_in_map_bound(t_mini_map map, double x, double y)
{
	double	dist_to_center;

	dist_to_center = sqrtf(powf(x - map.x, 2) + powf(y - map.y, 2));
	if (dist_to_center <= map.radius && dist_to_center <= map.radius - 1)
		return (1);
	return (0);
}

void	ft_draw_circle(int	*data, t_mini_map map, int color)
{
	int	border;
	int	cord[2];

	border = CENTER - map.radius;
	cord[0] = border;
	while (cord[0] <= border + (map.radius * 2))
	{
		cord[1] = border;
		while (cord[1] <= border + (map.radius * 2))
		{
			if (ft_is_in_map_bound(map, cord[1], cord[0]))
				data[cord[0] * WIDTH + cord[1]] = color;
			cord[1]++;
		}
		cord[0]++;
	}
}

void	ft_render_mini_map(t_data *data)
{
	t_mini_map	mini_map;
	t_mini_map	player;

	mini_map = ft_fill_mini_map_comp(CENTER, CENTER, RADIUS);
	player = ft_fill_mini_map_comp(CENTER, CENTER, PLAYER_R);
	ft_draw_circle(data->mlx.img.get_addr, mini_map,
		ft_create_color(0, 194, 187, 181));
	ft_draw_rays(data, mini_map);
	ft_draw_comps(data, mini_map);
	ft_draw_circle(data->mlx.img.get_addr, player,
		ft_create_color(0, 132, 158, 168));
}
