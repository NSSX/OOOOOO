/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:23:44 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:24:59 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

double		get_single_var(char *chaine)
{
	int		i;
	double	val;
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * ft_strlen(chaine));
	i = 0;
	val = 0;
	while (chaine[i] != '\0')
	{
		if (chaine[i] == '(')
		{
			if (chaine[i + 1] >= '0' && chaine[i + 1] <= '9')
				i++;
			while (chaine[i] >= '0' && chaine[i] <= '9' && chaine[i] != '\0')
			{
				tmp = ft_strjoin_carac(tmp, chaine[i]);
				i++;
			}
			return (ft_atoi(tmp));
		}
		i++;
	}
	return (val);
}

void		cut_obj(char *temp, t_obj *obj)
{
	char *here2;

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
	if ((here2 = ft_strstr(temp, "ref(")) && here2 != NULL)
	  {
	    here2 = chaine2(here2);
	    obj->ref = get_single_var(here2);
	    obj->ref /= 100;
	  }
	if ((here2 = ft_strstr(temp, "refraction(")) && here2 != NULL)
          {
            here2 = chaine2(here2);
            obj->refraction = get_single_var(here2);
            obj->refraction /= 100;
          }
	if ((here2 = ft_strstr(temp, "neg(")) && here2 != NULL)
          {
            here2 = chaine2(here2);
            obj->neg = get_single_var(here2);
          }
	if ((here2 = ft_strstr(temp, "pos1(")) && here2 != NULL)
          {
	    here2 = chaine2(here2);
	    obj->tab_pos[0] = *vec3d(here2);
          }
	if ((here2 = ft_strstr(temp, "pos2(")) && here2 != NULL)
          {
            here2 = chaine2(here2);
            obj->tab_pos[1] = *vec3d(here2);
          }
	if ((here2 = ft_strstr(temp, "pos3(")) && here2 != NULL)
          {
            here2 = chaine2(here2);
            obj->tab_pos[2] = *vec3d(here2);
          }
}

void		trait_obj(char *here, t_obj *obj)
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
	cut_obj(temp, obj);
}

void		cut_pov(char *temp, t_obj *obj)
{
	char *here2;

	if ((here2 = ft_strstr(temp, "size(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->size = get_single_var(here2);
	}
	if ((here2 = ft_strstr(temp, "dir(")) && here2 != NULL)
	{
		here2 = chaine2(here2);
		obj->rot = *vec3d(here2);
	}
}

void		trait_pov(char *here, t_obj *obj)
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
	}
	cut_pov(temp, obj);
}
