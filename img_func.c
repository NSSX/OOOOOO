/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:08:55 by avella            #+#    #+#             */
/*   Updated: 2016/06/09 13:00:06 by vle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void		my_pixel_put_to_image(t_img *myimg, int x, int y, int color)
{
	myimg->data = mlx_get_data_addr(myimg->img_ptr,
			&myimg->bpp, &myimg->sizeline, &myimg->endian);
	myimg->data[y * myimg->sizeline + x * myimg->bpp / 8] = color % 256;
	color /= 256;
	myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 1] = color % 256;
	color /= 256;
	myimg->data[y * myimg->sizeline + x * myimg->bpp / 8 + 2] = color % 256;
}

void		pixel_put_to_img(t_env *e, int x, int y)
{
	int color;

	color = (int)(e->pixel_color.z * 256) % 256;
	color += ((int)(e->pixel_color.y * 256) % 256) * 256;
	color += ((int)(e->pixel_color.x * 256) % 256) * 256 * 256;
	my_pixel_put_to_image(e->img, x, y, color);
}
