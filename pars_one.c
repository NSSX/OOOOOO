/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:19:50 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:26:25 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

void	err(void)
{
	ft_putstr("BAD PARSING POTO\n");
	exit(1);
}

t_obj	*create(void)
{
	t_obj *obj;

	obj = malloc(sizeof(t_obj));
	obj->type = 0;
	obj->size = 1;
	obj->pos = (t_vec3d){0, 0, 0};
	obj->color = (t_vec3d){0, 0, 0};
	obj->color.x = 0.4;
	obj->color.y = 0.4;
	obj->color.z = 0.4;
	obj->neg = 0;
	obj->intens = 0.5;
	obj->rot = (t_vec3d){0, 0, 0};
	obj->next = NULL;
	return (obj);
}

t_obj	*add_list(t_env *e)
{
	t_obj	*actual;
	t_obj	*new_obj;
	int		i;

	if (!e)
		return (NULL);
	actual = e->obj;
	i = 0;
	if (!actual)
	{
		e->obj = create();
		return (e->obj);
	}
	while (actual->next)
	{
		actual = actual->next;
	}
	new_obj = create();
	actual->next = new_obj;
	return (new_obj);
}

char	*chaine(char *ch)
{
	int i;

	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == '}')
		{
			ch = ft_strsub(ch, 0, i);
			return (ch);
		}
		i++;
	}
	return (NULL);
}

char	*chaine2(char *ch)
{
	int i;

	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == ')')
		{
			ch = ft_strsub(ch, 0, i + 1);
			return (ch);
		}
		i++;
	}
	return (NULL);
}
