/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:39 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/18 21:18:47 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = result_line(fd, backup, buffer);
	free(buffer);
	if (line == NULL || line[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = save_backup(line);
	return (line);
}

char	*result_line(int fd, char *backup, char *buffer)
{
	char	*temp;
	int		len;

	len = 0;
	while (1)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == 0)
			break ;
		if (len == -1)
			return (NULL);
		buffer[len] = '\0';
		if (backup == NULL)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		if (backup == NULL)
			return (NULL);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

char	*save_backup(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	tmp = ft_strdup(&line[i + 1]);
	if (tmp == NULL)
		return (NULL);
	line[i + 1] = '\0';
	return (tmp);
}

//backup, buffer, line
//static 구조체 (fd, backup, next)
//char * buffer, line