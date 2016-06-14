/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_give.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 16:45:33 by avella            #+#    #+#             */
/*   Updated: 2016/06/09 13:55:14 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	init_env(t_env *e)
{
	t_vec3d	give;

	e->obj = NULL;
	e->obj_tmp = NULL;
	e->nl = 0;
	e->name = "RayTracer V10000";
	e->width = WIDTH;
	e->height = HEIGHT;
	give = (t_vec3d){0, 0, 0};
	e->eye_pos = give;
	give = (t_vec3d){0, 0, 0};
	e->eye_dir = give;
	e->ambient_light = (t_vec3d){0,0,0};
}

void	get_lightspot_number(t_env *e)
{
	t_obj *tmp;

	tmp = e->obj;
	while (tmp)
	{
		if (tmp->type == 8)
			e->nl += 1.0;
		tmp = tmp->next;
	}
}

void	init_eye(t_env *e)
{
	e->eye_pos.x = 0;
	e->eye_pos.y = 1;
	e->eye_pos.z = 0;
	e->eye_dir.x = 0;
	e->eye_dir.y = 1;
	e->eye_dir.z = 0;
}

void	init_viewpoint(t_env *e)
{
	t_obj *viewpoint;

	viewpoint = e->obj;
	while (viewpoint)
	{
		if (viewpoint->type == 9)
		{
			e->eye_pos.x = viewpoint->pos.x;
			e->eye_pos.y = viewpoint->pos.y;
			e->eye_pos.z = viewpoint->pos.z;
			e->eye_dir.x = viewpoint->rot.x;
			e->eye_dir.y = viewpoint->rot.y;
			e->eye_dir.z = viewpoint->rot.z;
		}
		viewpoint = viewpoint->next;
	}
}
