/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:39 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/27 16:57:53 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*result_line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	line = make_line(fd, backup, buffer);
	free(buffer);
	if (line == NULL || line[0] == '\0')
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = save_backup(&line);
	if (!backup)
	{
		// all free
		// null return
	}
	result_line = cut_line(&line);
	if (!backup)
	{
		// all free
		// null return
	}
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
			return (NULL);
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

	// char *new_line = ft_strdup(*line); // Add this line
	// free(*line); // And this line
	// *line = new_line; // And this line

	backup = ft_strdup((*line) + i + 1);
	if (backup == NULL)
	{
		free(*line);
		return (NULL);
	}
	(*line)[i + 1] = '\0';
	return (backup);
}
//abcd\n1234
//abcd\n1234
//라인이 잘 못됐을 때 백업을 프리해줬었다
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
	{
		free(*line);
		return (NULL);
	}
	return (result_line);
}
////abc\n12345
////abc\n\02345
//a\0

//backup, buffer, line
//static 구조체 (fd, backup, next)
//char * buffer, line