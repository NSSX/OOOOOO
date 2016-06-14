/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:45:14 by avella            #+#    #+#             */
/*   Updated: 2016/05/27 17:46:26 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double norme_vector(t_vec3d *vec)
{
  double n;

  n = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
  return(n);
}

void		ajust(t_vec3d *vec)
{
	double n;

	n = 1.0 / sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));
	vec->x *= n;
	vec->y *= n;
	vec->z *= n;
}

double		mult(t_vec3d *a, t_vec3d *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_vec3d		x_moin_x(t_vec3d *a, t_vec3d *b)
{
	t_vec3d v;

	v.x = a->y * b->z - a->z * b->y;
	v.y = a->z * b->x - a->x * b->z;
	v.z = a->x * b->y - a->y * b->x;
	return (v);
}

t_vec3d		a_moin_b(t_vec3d *a, t_vec3d *b)
{
	t_vec3d v;

	v.x = a->x - b->x;
	v.y = a->y - b->y;
	v.z = a->z - b->z;
	return (v);
}

t_vec3d		a_plus_x(t_vec3d *a, double x)
{
	t_vec3d v;

	v.x = a->x + x;
	v.y = a->y + x;
	v.z = a->z + x;
	return (v);
}
