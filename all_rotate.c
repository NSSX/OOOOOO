/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:04:06 by avella            #+#    #+#             */
/*   Updated: 2016/05/26 17:04:52 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void		rotate_x(double *x, double *y, double *z, double angle)
{
	double		y_tmp;
	double		z_tmp;

	(void)*x;
	angle = CONV_RAD(angle);
	y_tmp = *y;
	z_tmp = *z;
	*y = y_tmp * cos(angle) - z_tmp * sin(angle);
	*z = y_tmp * sin(angle) + z_tmp * cos(angle);
}

void		rotate_y(double *x, double *y, double *z, double angle)
{
	double			x_tmp;
	double			z_tmp;

	(void)*y;
	angle = CONV_RAD(angle);
	x_tmp = *x;
	z_tmp = *z;
	*z = z_tmp * cos(angle) - x_tmp * sin(angle);
	*x = z_tmp * sin(angle) + x_tmp * cos(angle);
}

void		rotate_z(double *x, double *y, double *z, double angle)
{
	double		x_tmp;
	double		y_tmp;

	(void)*z;
	angle = CONV_RAD(angle);
	x_tmp = *x;
	y_tmp = *y;
	*x = x_tmp * cos(angle) - y_tmp * sin(angle);
	*y = x_tmp * sin(angle) + y_tmp * cos(angle);
}
