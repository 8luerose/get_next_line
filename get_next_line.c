/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:39 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/17 22:40:40 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include get_next_line

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*get_next_line(int fd);
{

}