/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:05:35 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:29:39 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

int			shadow_cyl(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		sl;

	sl = (t_vec3d){e->sl.x, e->sl.y, e->sl.z};
	eo = eye_or(e->pos, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(sl.x), &(sl.y), &(sl.z), -obj->rot.x);
	rotate_y(&(sl.x), &(sl.y), &(sl.z), -obj->rot.y);
	rotate_z(&(sl.x), &(sl.y), &(sl.z), -obj->rot.z);
	a = sl.x * sl.x + sl.z * sl.z;
	b = sl.x * eo.x + sl.z * eo.z;
	c = eo.x * eo.x + eo.z * eo.z - obj->size * obj->size;
	e->det = b * b - a * c;
	if (e->det > 0.001)
		return (ret_val2(a, b, e->det, e));
	return (0);
}

int			shadow_sphere(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		sl;

	sl = (t_vec3d){e->sl.x, e->sl.y, e->sl.z};
	eo = eye_or(e->pos, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(sl.x), &(sl.y), &(sl.z), -obj->rot.x);
	rotate_y(&(sl.x), &(sl.y), &(sl.z), -obj->rot.y);
	rotate_z(&(sl.x), &(sl.y), &(sl.z), -obj->rot.z);
	a = mult(&(sl), &(sl));
	b = mult(&eo, &(sl));
	c = mult(&eo, &eo) - obj->size * obj->size;
	e->det = b * b - a * c;
	if (e->det > 0.001)
		return (ret_val2(a, b, e->det, e));
	return (0);
}

int			shadow_cone(t_obj *obj, t_env *e)
{
	t_vec3d		eo;
	double		a;
	double		b;
	double		c;
	t_vec3d		sl;

	sl = (t_vec3d){e->sl.x, e->sl.y, e->sl.z};
	eo = eye_or(e->pos, obj->pos);
	rotate_x(&(eo.x), &(eo.y), &(eo.z), -obj->rot.x);
	rotate_y(&(eo.x), &(eo.y), &(eo.z), -obj->rot.y);
	rotate_z(&(eo.x), &(eo.y), &(eo.z), -obj->rot.z);
	rotate_x(&(sl.x), &(sl.y), &(sl.z), -obj->rot.x);
	rotate_y(&(sl.x), &(sl.y), &(sl.z), -obj->rot.y);
	rotate_z(&(sl.x), &(sl.y), &(sl.z), -obj->rot.z);
	a = sl.x * sl.x - sl.y * sl.y + sl.z * sl.z;
	b = sl.x * eo.x - sl.y * eo.y + sl.z * eo.z;
	c = eo.x * eo.x + eo.z * eo.z - eo.y * eo.y;
	e->det = b * b - a * c;
	if (e->det > 0.001)
		return (ret_val2(a, b, e->det, e));
	return (0);
}

double		give_shadow(t_env *e)
{
	t_obj	*obj;
	double	my_shadow;
	double	give;

	obj = e->obj;
	my_shadow = 1;
	while (obj)
	{
		if (obj->type == 8)
		{
			give = inter_shadow(e, &obj->pos);
			if (give == 1)
			  my_shadow -= (obj->intens + e->nl) / 2;
		}
		obj = obj->next;
	}
	return (lim(my_shadow, 0, 1));
}

double		inter_shadow(t_env *e, t_vec3d *my_pos)
{
	t_obj	*subs;
	int		give;
	int		my_shadow;

	subs = e->obj;
	give = 0;
	my_shadow = 0;
	e->sl = a_moin_b(my_pos, &(e->pos));
	e->sz = sqrt(e->sl.x * e->sl.x + e->sl.y * e->sl.y + e->sl.z * e->sl.z);
	e->sl.x = e->sl.x / e->sz;
	e->sl.y = e->sl.y / e->sz;
	e->sl.z = e->sl.z / e->sz;
	while (subs)
	{
		if (subs->type == 1)
			give = shadow_sphere(subs, e);
		else if (subs->type == 3)
			give = shadow_cyl(subs, e);
		else if (subs->type == 2)
			give = shadow_cone(subs, e);
		if (give == 1)
			my_shadow = 1;
		subs = subs->next;
	}
	return (my_shadow);
}
