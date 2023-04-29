/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:39 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/29 19:39:46 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*result_line;
	char		buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = make_line(fd, backup, buffer);
	if (line == NULL || line[0] == '\0')
	{
		if (line != 0)
			free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = save_backup(&line);
	if (backup == NULL && line == NULL)
		return (NULL);
	result_line = cut_line(&line);
	if (result_line == NULL)
		return (gnl_free(&backup));
	free (line);
	return (result_line);
}

char	*make_line(int fd, char *backup, char *buffer)
{
	char	*temp;
	int		len;

	while (1)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		if (len == 0)
			break ;
		if (len == -1)
			return (gnl_free(&backup));
		buffer[len] = '\0';
		if (backup == NULL)
			backup = ft_strdup("");
		if (!backup)
			return (NULL);
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (backup == NULL)
			return (NULL);
		if (ft_strchr(backup, '\n'))
			break ;
	}
	return (backup);
}

char	*save_backup(char **line)
{
	char	*backup;
	int		i;

	i = 0;
	while ((*line)[i] != '\0' && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\0' || (*line)[i + 1] == '\0')
		return (NULL);
	backup = ft_strdup((*line) + i + 1);
	if (backup == NULL)
		return (gnl_free(line));
	(*line)[i + 1] = '\0';
	return (backup);
}

char	*cut_line(char **line)
{
	int		i;
	char	*result_line;

	i = 0;
	while ((*line)[i] != '\0' && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\0')
		result_line = ft_strdup(*line);
	else
		result_line = ft_substr(*line, 0, i + 1);
	if (result_line == NULL)
		return (gnl_free(line));
	return (result_line);
}

char	*gnl_free(char **p)
{
	free(*p);
	*p = NULL;
	return (NULL);
}

#include <stdio.h>

int	main(void)
{	
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
	}
	fd = open("./test.txt", O_RDONLY);
	return (0);
}
