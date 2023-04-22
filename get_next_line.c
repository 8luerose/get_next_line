/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:39 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/22 15:01:45 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line. h"

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
		backup = NULL;
		return (NULL);
	}
	backup = save_backup(&line);
	if (!backup)
		line = NULL;
	return (line);
}
////abc\n\02
//a\0
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
		if (!backup)
			return (NULL);
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (backup == NULL)
			return (NULL);
		temp = NULL;
		if (ft_strchr(backup, '\n'))
			break ;
	}
	return (backup);
}

char	*save_backup(char **a)
{
	char	*tmp;
	char	*line;
	int		i;
	int		len;

	i = 0;
	line = *a;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	tmp = ft_strdup(&line[i + 1]);
	if (tmp == NULL)
	{
		free(line);
		return (NULL);
	}
	len = i + 1;
	line[len] = '\0';
	*a = ft_strdup(line);
	line[len] = '1';
	free(line);
	if (!*a)
		return (0);
	return (tmp);
}
////abc\n\02899999 free(line + i + 1);
//a\0


//backup, buffer, line
//static 구조체 (fd, backup, next)
//char * buffer, line 