/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:27:30 by ahkalama          #+#    #+#             */
/*   Updated: 2024/02/27 15:30:32 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void	ft_door_sprite(t_data *data)
{
	t_list		*temp;
	t_list		*next;
	t_object	*door;
	double		new_frame;

	temp = data->map.ll_door;
	while (temp)
	{
		door = (t_object *)temp->data;
		if (data->map.map[(int)door->y][(int)door->x] == OPENED_DOOR)
			new_frame = door->frame + DOOR_FRAME;
		else
			new_frame = door->frame - DOOR_FRAME;
		if ((int)new_frame < data->map.door.frames)
			door->frame = new_frame;
		if (door->frame <= 0)
		{
			next = temp->next;
			ft_ll_remove(&data->map.ll_door, door->x, door->y);
			temp = next;
		}
		else
			temp = temp->next;
	}
}

void	ft_open_close_door(t_data *data)
{
	t_coordinates	door;

	door = ft_wall_hit(data, data->player.pos, data->player.angle, NULL);
	if (!ft_strchr(DOORS, data->map.map[(int)door.y][(int)door.x]))
		return ;
	if (ft_distance(data->player.pos, door) > OFF_SET * 4.0)
		return ;
	if (data->map.map[(int)door.y][(int)door.x] == CLOSED_DOOR
		&& ft_ll_find(data->map.ll_door, door.x, door.y) == 0)
	{
		ll_add_head(&(data->map.ll_door),
			ll_new(ft_create_obj(0, door.x, door.y)));
		data->map.map[(int)door.y][(int)door.x] = OPENED_DOOR;
	}
	else if (data->map.map[(int)door.y][(int)door.x] == OPENED_DOOR
			&& ft_ll_find(data->map.ll_door,
				door.x, door.y) == data->map.door.frames - 1)
		data->map.map[(int)door.y][(int)door.x] = CLOSED_DOOR;
}
