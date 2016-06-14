/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:13:02 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:29:09 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

int			expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img->img_ptr, 0, 0);
	return (1);
}

void		another_keycode(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 126)
		e->v2 += 0.2;
	if (keycode == 124)
		e->v += 0.2;
	if (keycode == 125)
		e->v2 -= 0.2;
	if (keycode == 123)
		e->v -= 0.2;
}

void		norme_obj_rot(int action, t_obj *obj)
{
	if (action == 7)
		obj->pos.x += 1;
	else if (action == 8)
		obj->pos.x -= 1;
	else if (action == 9)
		obj->pos.z -= 1;
	else if (action == 10)
		obj->pos.z += 1;
}

void		obj_rot(t_env *e, int action, int etat)
{
	t_obj *obj;

	obj = e->obj;
	while (obj)
	{
		if (obj->type == etat)
		{
			if (action == 1)
				obj->rot.z += 5;
			else if (action == 2)
				obj->rot.z -= 5;
			else if (action == 3)
				obj->rot.x -= 5;
			else if (action == 4)
				obj->rot.x += 5;
			else if (action == 5)
				obj->pos.y += 1;
			else if (action == 6)
				obj->pos.y -= 1;
			else
				norme_obj_rot(action, obj);
		}
		obj = obj->next;
	}
}

void		movable(int keycode, t_env *e, int etat)
{
	if (keycode == 43)
		obj_rot(e, 1, etat);
	if (keycode == 47)
		obj_rot(e, 2, etat);
	if (keycode == 44)
		obj_rot(e, 3, etat);
	if (keycode == 39)
		obj_rot(e, 4, etat);
	if (keycode == 69)
		obj_rot(e, 5, etat);
	if (keycode == 78)
		obj_rot(e, 6, etat);
	if (keycode == 67)
		obj_rot(e, 7, etat);
	if (keycode == 75)
		obj_rot(e, 8, etat);
	if (keycode == 81)
		obj_rot(e, 9, etat);
	if (keycode == 91)
		obj_rot(e, 10, etat);
}
