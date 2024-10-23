/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:41:05 by namichel          #+#    #+#             */
/*   Updated: 2024/10/21 01:29:53 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*str;

	i = 0;
	len_s = ft_strlen(s);
	if (len >= len_s - start)
		len = len_s - start;
	if (start >= len_s)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (start < len_s && i < len)
		str[i++] = (char)s[start++];
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(const char *theString)
{
	size_t	index;

	index = 0;
	while (theString[index])
		index++;
	return (index);
}

char	*ft_strjoin(const char *s1, char const *s2)
{
	int		i;
	int		a;
	int		b;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	i = -1;
	ptr = malloc(sizeof(char) * (a + b + 1));
	if (!ptr)
		return (NULL);
	while (++i < a)
		ptr[i] = s1[i];
	i--;
	while (++i - a < b)
		ptr[i] = s2[i - a];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strdup(const char *source)
{
	char	*result;
	size_t	len;

	len = ft_strlen(source) + 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_memcpy(result, source, len);
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}
