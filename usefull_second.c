/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:17:03 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:27:27 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double		lim(double x, double min, double max)
{
	if (x < min)
		x = min;
	else if (x > max)
		x = max;
	return (x);
}

void		limit_for_vec(t_vec3d *vec, double a, double b)
{
	vec->x = lim(vec->x, a, b);
	vec->y = lim(vec->y, a, b);
	vec->z = lim(vec->z, a, b);
}

t_vec3d		plus(t_vec3d *a, t_vec3d *b)
{
	t_vec3d v;

	v.x = a->x + b->x;
	v.y = a->y + b->y;
	v.z = a->z + b->z;
	return (v);
}

t_vec3d		a_x_b(t_vec3d *a, t_vec3d *b)
{
	t_vec3d val;

	val.x = a->x * b->x;
	val.y = a->y * b->y;
	val.z = a->z * b->z;
	return (val);
}

t_vec3d		mult_value(t_vec3d *a, double value)
{
	t_vec3d v;

	v.x = a->x * value;
	v.y = a->y * value;
	v.z = a->z * value;
	return (v);
}
