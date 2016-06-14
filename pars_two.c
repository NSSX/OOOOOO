/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 15:21:47 by avella            #+#    #+#             */
/*   Updated: 2016/05/28 15:28:45 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_h.h"

char		*ft_strjoin_carac(char const *s1, char s2)
{
	char		*chaine;
	int			index;
	int			index2;

	index2 = 0;
	index = 0;
	if (!s1 || !s2)
		return (NULL);
	chaine = ft_memalloc(sizeof(char) * (ft_strlen(s1) + 10));
	if (chaine == NULL)
		return (NULL);
	while (s1[index] != '\0')
	{
		chaine[index] = s1[index];
		index++;
	}
	chaine[index] = s2;
	index++;
	index2++;
	chaine[index] = '\0';
	return (chaine);
}

void		norme_val1(char *chaine, t_pars *pars)
{
	if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9')
			|| chaine[pars->i + 1] == '-')
		pars->i++;
	else
		err();
	while (chaine[pars->i] != ',' && chaine[pars->i] != '\0')
	{
		pars->val1 = ft_strjoin_carac(pars->val1, chaine[pars->i]);
		pars->i++;
	}
	if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9')
			|| chaine[pars->i + 1] == '-')
		pars->i++;
	else
		err();
}

void		norme_val2(char *chaine, t_pars *pars)
{
	while (chaine[pars->i] != ',' && chaine[pars->i] != '\0')
	{
		pars->val2 = ft_strjoin_carac(pars->val2, chaine[pars->i]);
		pars->i++;
	}
	if ((chaine[pars->i + 1] >= '0' && chaine[pars->i + 1] <= '9')
			|| chaine[pars->i + 1] == '-')
		pars->i++;
	else
		err();
}

void		norme_val3(char *chaine, t_pars *pars)
{
	while (chaine[pars->i] != ',' && chaine[pars->i] != '\0'
			&& chaine[pars->i] != ')')
	{
		pars->val3 = ft_strjoin_carac(pars->val3, chaine[pars->i]);
		pars->i++;
	}
}

t_vec3d		*vec3d(char *chaine)
{
	t_pars	pars;
	t_vec3d	*tab;

	tab = malloc(sizeof(t_vec3d) * 1);
	pars.val1 = ft_memalloc(ft_strlen(chaine));
	pars.val2 = ft_memalloc(ft_strlen(chaine));
	pars.val3 = ft_memalloc(ft_strlen(chaine));
	pars.i = 0;
	while (chaine[pars.i] != '\0')
	{
		if (chaine[pars.i] == '(')
		{
			norme_val1(chaine, &pars);
			norme_val2(chaine, &pars);
			norme_val3(chaine, &pars);
			tab->x = ft_atoi(pars.val1);
			tab->y = ft_atoi(pars.val2);
			tab->z = ft_atoi(pars.val3);
			return (tab);
		}
		pars.i++;
	}
	return (NULL);
}
