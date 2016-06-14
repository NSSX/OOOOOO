/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/27 17:48:06 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:09:13 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"
#include "get_next_line.h"
#include <fcntl.h>

void	cut_spot(char *temp, t_obj *obj)
{
	char *here2;

	if ((here2 = ft_strstr(temp, "int(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->intens = get_single_var(here2);
		obj->intens = lim(obj->intens, 0.0, 99.0);
		obj->intens /= 100;
	}
	if ((here2 = ft_strstr(temp, "size(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->size = get_single_var(here2);
		obj->size /= 100;
	}
	if ((here2 = ft_strstr(temp, "rot(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->rot = *vec3d(here2);
	}
}

void	trait_spot(char *here, t_obj *obj)
{
	char	*here2;
	char	*temp;

	temp = chaine(here);
	here[0] = 'W';
	if (temp == NULL)
		return ;
	if ((here2 = ft_strstr(temp, "pos(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->pos = *vec3d(here2);
	}
	if ((here2 = ft_strstr(temp, "color(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->color = *vec3d(here2);
		obj->color.x = lim(obj->color.x / 256, 0, 1);
		obj->color.y = lim(obj->color.y / 256, 0, 1);
		obj->color.z = lim(obj->color.z / 256, 0, 1);
	}
	cut_spot(temp, obj);
}

int		in(t_env *e, char *here, int type, int end)
{
	t_obj *obj;

	obj = add_list(e);
	if (type == 9)
		trait_pov(here, obj);
	else if (type == 8)
		trait_spot(here, obj);
	else
		trait_obj(here, obj);
	obj->type = type;
	end++;
	return (end);
}

void	traitement(char *file, t_env *e)
{
	char	*here;
	int		end;

	end = 0;
	if ((here = ft_strstr(file, "sphere{\n")) && here != NULL)
		end = in(e, here, 1, end);
	if ((here = ft_strstr(file, "cone{\n")) && here != NULL)
		end = in(e, here, 2, end);
	if ((here = ft_strstr(file, "cylinder{\n")) && here != NULL)
		end = in(e, here, 3, end);
	if ((here = ft_strstr(file, "triangle{\n")) && here != NULL)
	  end = in(e, here, 4, end);
	if ((here = ft_strstr(file, "plane{\n")) && here != NULL)
		end = in(e, here, 0, end);
	if ((here = ft_strstr(file, "pov{\n")) && here != NULL)
		end = in(e, here, 9, end);
	if ((here = ft_strstr(file, "spot{\n")) && here != NULL)
		end = in(e, here, 8, end);
	if (end != 0)
		traitement(file, e);
}

void	parsing(t_env *e, int argc, char *av)
{
	int		fd;
	char	*yt;
	char	*file;
	int		ret;

	e->obj = NULL;
	ret = 0;
	file = ft_memalloc(sizeof(char) * 1);
	if (argc != 2)
	{
		ft_putstr("bad arg\n");
		exit(1);
	}
	fd = 0;
	fd = open(av, O_RDONLY);
	while ((ret = get_next_line(fd, &yt)) && ret != -1)
	{
		file = ft_strjoin(file, yt);
		file = ft_strjoin(file, "\n");
	}
	traitement(file, e);
}
