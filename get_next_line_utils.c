/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:56:37 by taehkwon          #+#    #+#             */
/*   Updated: 2023/04/21 20:30:13 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*arr;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	arr = (char *)malloc((len + 1) * (sizeof(char)));
	if (!(arr))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		arr[i] = s1[i];
		i++;
	}
	arr[len] = '\0';
	return (arr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = (unsigned char *)dst;
	src_p = (unsigned char *)src;
	if (n == 0 || dst == src)
		return (dst);
	while (n--)
	{
		*dst_p = *src_p;
		dst_p++;
		src_p++;
	}
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;
	char	*result_cpy;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result)
		return (0);
	// result_cpy = result;
	// while (s1)
	// 	result_cpy++ = s1++;
	// while (s2)
	// 	result_cpy++ = s2++;
	result_cpy = result;
	while (*s1)
		*(result_cpy++) = *(s1++);
	while (*s2)
		*(result_cpy++) = *(s2++);
	// ft_memcpy (result, s1, s1_len);
	// ft_memcpy (result + s1_len, s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	result_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	result_len = s_len - start;
	if (result_len > len)
		result_len = len;
	result = (char *)malloc((result_len + 1) * sizeof(char));
	if (!result)
		return (0);
	ft_memcpy(result, s + start, result_len);
	result[result_len] = '\0';
	return (result);
}
