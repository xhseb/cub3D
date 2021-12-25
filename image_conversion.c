/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonkang <sonkang@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:17:32 by sonkang           #+#    #+#             */
/*   Updated: 2021/12/25 23:47:10 by sonkang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_init2(t_info *info)
{
	//notion에 정리
	if (info->dda.raydir_x < 0)
	{
		info->dda.step_x = -1;
		info->dda.sidedist_x = (info->user.pos_x - info->dda.map_x) * \
			info->dda.deltadist_x;
	}
	else
	{
		info->dda.step_x = 1;
		info->dda.sidedist_x = (info->dda.map_x + 1 - info->user.pos_x) * \
			info->dda.deltadist_x;
	}
	if (info->dda.raydir_y < 0)
	{
		info->dda.step_y = -1;
		info->dda.sidedist_y = (info->user.pos_y - info->dda.map_y) * \
			info->dda.deltadist_y;
	}
	else
	{
		info->dda.step_y = 1;
		info->dda.sidedist_y = (info->dda.map_y + 1 - info->user.pos_y) * \
			info->dda.deltadist_y;
	}
}

void	dda_init(t_info *info, int x)
{
	//x값에 따른 win_w에 대한 비율을 구한다 (-1 ~ 1)
	info->dda.camera_x = 2 * x / (double)info->win.win_w - 1;
	//비율을 plane에 곱한 것을 더해서 광선의 방향을 구함
	info->dda.raydir_x = info->user.dir_x + info->user.plane_x * \
		info->dda.camera_x;
	info->dda.raydir_y = info->user.dir_y + info->user.plane_y * \
		info->dda.camera_x;
	info->dda.map_x = (int)info->user.pos_x;
	info->dda.map_y = (int)info->user.pos_y;
	//노션 정리
	info->dda.deltadist_x = fabs(1 / info->dda.raydir_x);
	info->dda.deltadist_y = fabs(1 / info->dda.raydir_y);
	info->dda.hit = 0;
	dda_init2(info);
}

void	check_hit(t_info *info)
{
	//side가 0이라면 y면에 부딪힘 1이라면 x면에 부딪힘
	while (info->dda.hit == 0)
	{
		if (info->dda.sidedist_x < info->dda.sidedist_y)
		{
			info->dda.sidedist_x += info->dda.deltadist_x;
			info->dda.map_x += info->dda.step_x;
			info->dda.side = 0;
		}
		else
		{
			info->dda.sidedist_y += info->dda.deltadist_y;
			info->dda.map_y += info->dda.step_y;
			info->dda.side = 1;
		}
		if (info->map.map[info->dda.map_y][info->dda.map_x] == '1' || \
				info->map.map[info->dda.map_y][info->dda.map_x] == ' ')
			info->dda.hit = 1;
	}
}

int	img_conv(t_info *info)
{
	int		x;

	x = -1;
	while (++x < info->win.win_w)
	{
		dda_init(info, x);
		check_hit(info);
		//어안효과를 방지하기 위해 실제 거리를 구함
		if (info->dda.side == 0)
			info->dda.perp = (info->dda.map_x - info->user.pos_x + \
				(1 - info->dda.step_x) / 2) / info->dda.raydir_x;
		else
			info->dda.perp = (info->dda.map_y - info->user.pos_y + \
				(1 - info->dda.step_y) / 2) / info->dda.raydir_y;
		//플레이어와 벽사이의 거리와 win_h의 비율을 구한다
		info->dda.line_height = (int)(info->win.win_h / info->dda.perp);
		//벽이 화면의 중간에서 그려져야 하기 때문에 info->win.win_h / 2에 길이를 더하거나 뺀다
		info->dda.draw_start = info->win.win_h / 2 - info->dda.line_height / 2;
		if (info->dda.draw_start < 0)
			info->dda.draw_start = 0;
		info->dda.draw_end = info->win.win_h / 2 + info->dda.line_height / 2;
		if (info->dda.draw_end >= info->win.win_h)
			info->dda.draw_end = info->win.win_h - 1;
		affine_texture_mapping(info, x);
	}
	draw(info);
	return (0);
}
