/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inicole- <inicole-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 01:40:58 by inicole-          #+#    #+#             */
/*   Updated: 2022/06/21 18:49:23 by inicole-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_save(int fd, char *backup, char	*buffer);
static char	*make_line(char *backup);
static char	*newbackup(char *backup);

char	*get_next_line(int fd)
{
	char		*l;
	static char	*b;
	char		*buff;

	l = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(buff);
		return (NULL);
	}
	b = read_save(fd, b, buff);
	if (!b)
		return (NULL);
	l = make_line(b);
	b = newbackup(b);
	return (l);
}

static char	*read_save(int fd, char *backup, char	*buffer)
{
	int		read_buff;
	int		i;
	char	*tmp;

	read_buff = 1;
	i = 0;
	while (i == 0 && read_buff != 0)
	{
		read_buff = read(fd, buffer, BUFFER_SIZE);
		if (read_buff == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_buff] = '\0';
		if (!backup)
			backup = ft_strdup("");
		tmp = backup;
		backup = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(backup, '\n'))
			i = 1;
	}
	free(buffer);
	return (backup);
}

static char	*make_line(char *backup)
{
	int			i;
	char		*l;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	l = (char *) malloc (sizeof(char) * (i + 2));
	if (!l)
		return (NULL);
	ft_strlcpy(l, backup, i + 2);
	if (l[0] == '\0')
	{
		free(l);
		return (NULL);
	}
	return (l);
}

static char	*newbackup(char *backup)
{
	int			i;
	char		*nb;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\0')
	{
		free(backup);
		return (NULL);
	}
	nb = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!nb)
		return (NULL);
	ft_strlcpy(nb, backup + i + 1, ft_strlen(backup) - i + 1);
	free(backup);
	return (nb);
}
