/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avella <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 15:15:22 by avella            #+#    #+#             */
/*   Updated: 2016/01/06 18:58:30 by avella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int		lineorend(char *chaine)
{
	int result;
	int i;

	i = 0;
	result = 4;
	while (chaine[i] && result == 4 && chaine[i] != EOF)
	{
		if (chaine[i] == '\n')
			result = 1;
		i++;
	}
	if (chaine[i] == EOF && result == 4)
		result = 0;
	if (!chaine[i] && result == 4)
		result = 0;
	return (result);
}

int		amalloc(char *chaine)
{
	int i;

	i = 0;
	while (chaine[i] != '\n' && chaine[i] != '\0' && chaine[i] != EOF)
		i++;
	return (i);
}

int		give_thereturn(char *chaine, int ret)
{
	int thereturn;

	thereturn = 4;
	if (ret == -1)
		thereturn = -1;
	else if (lineorend(chaine) == 1)
		thereturn = 1;
	else if (lineorend(chaine) == 0 && ret == 0)
		thereturn = 0;
	return (thereturn);
}

char	**my_line(char **chaine, int fd, char **line, int mall)
{
	int i;

	i = 0;
	mall = amalloc(chaine[fd]);
	line[0] = ft_strnew(mall + 1);
	while (i < mall)
	{
		line[0][i] = chaine[fd][i];
		i++;
	}
	line[0][i] = '\0';
	i = 0;
	while (chaine[fd][i] != '\n' && chaine[fd][i] != '\0')
		i++;
	i++;
	chaine[fd] = ft_strsub(chaine[fd], i, ft_strlen(chaine[fd]));
	return (line);
}

int		get_next_line(int const fd, char **line)
{
	int			thereturn;
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char	**chaine;
	int			mall;

	mall = 0;
	thereturn = 4;
	if (fd < 0 || line == NULL)
		return (-1);
	if (!chaine)
		chaine = (char **)malloc(sizeof(char *) * 100);
	if (!chaine[fd])
		chaine[fd] = ft_strnew(BUFF_SIZE + 1);
	while (thereturn == 4)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)))
		{
			buf[ret] = '\0';
			chaine[fd] = ft_strjoin(chaine[fd], buf);
		}
		thereturn = give_thereturn(chaine[fd], ret);
	}
	my_line(chaine, fd, line, mall);
	return (thereturn);
}
