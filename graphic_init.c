/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonkang <sonkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:17:24 by sonkang           #+#    #+#             */
/*   Updated: 2021/12/25 19:49:40 by sonkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	win_init(t_win *win)
{
	win->win_w = 1024;
	win->win_h = 768;
}

void	direction_init2(t_info *info)
{
	if (info->map.direction == 'E')
	{
		info->user.dir_x = 1;
		info->user.plane_y = 0.66;
		info->user.plane_x = 0.0;
	}
	else
	{
		info->user.dir_x = -1;
		info->user.plane_y = -0.66;
		info->user.plane_x = 0.0;
	}
	info->user.dir_y = 0;
}

void	direction_init(t_info *info)
{
	if (info->map.direction == 'N' || info->map.direction == 'S')
	{
		if (info->map.direction == 'N')
		{
			info->user.dir_y = -1;
			info->user.plane_y = 0.0;
			info->user.plane_x = 0.66;
		}
		else
		{
			info->user.dir_y = 1;
			info->user.plane_y = 0.0;
			info->user.plane_x = -0.66;
		}
		info->user.dir_x = 0;
	}
	else
		direction_init2(info);
}

void	user_init(t_info *info)
{
	direction_init(info);
	info->user.move_speed = 0.1;
	info->user.rot_speed = 0.1;
	info->user.pos_x = info->map.player_x + 0.5;
	info->user.pos_y = info->map.player_y + 0.5;
	//처음에 플레이어가 생성이 될 때 (n.0, m.0)으로 생성된다면 벽과의 거리가 0이 되기 때문에 조금의 거리를 두고 생성되게 한다.
	info->map.map[info->map.player_y][info->map.player_x] = '0';
}

void	grap_init(t_info *info)
{
	user_init(info);
	win_init(&(info->win));
	info->grap.img_width = 64;
	info->grap.img_height = 64;
}
