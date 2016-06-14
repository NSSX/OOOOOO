/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_cool_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:15:23 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:28:59 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

t_vec3d		eye_or(t_vec3d ray_or, t_vec3d pos)
{
	t_vec3d ret;

	ret.x = ray_or.x - pos.x;
	ret.y = ray_or.y - pos.y;
	ret.z = ray_or.z - pos.z;
	return (ret);
}

double		ret_val(double a, double b, double det)
{
	return ((-b - sqrt(det)) / a);
}

int			ret_val2(double a, double b, double det, t_env *e)
{
	det = (-b - sqrt(det)) / a;
	return ((det > 0.001) && (det < e->sz));
}

void		print_obj(int etat)
{
	if (etat == 0)
		ft_putstr(" plan\n");
	else if (etat == 1)
		ft_putstr(" sphere\n");
	else if (etat == 2)
		ft_putstr(" cone\n");
	else if (etat == 3)
		ft_putstr(" cylindre\n");
}
