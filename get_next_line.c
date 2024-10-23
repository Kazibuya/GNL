/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:40:42 by namichel          #+#    #+#             */
/*   Updated: 2024/10/21 02:41:34 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst != src)
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

static char	*read_fd(int fd, char *buffer, char *residue)
{
	long long	count;
	char		*temp;

	count = 1;
	while (count)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1)
			return (0);
		else if (count == 0)
			break ;
		buffer[count] = '\0';
		if (!residue)
			residue = ft_strdup("");
		temp = residue;
		residue = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (residue);
}

static char	*recover_residue(char *str)
{
	long long	count;
	char		*residue;

	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\0')
		return (0);
	residue = ft_substr(str, count + 1, ft_strlen(str) - count);
	if (*residue == '\0')
	{
		free (residue);
		residue = NULL;
	}
	str[count + 1] = '\0';
	return (residue);
}

char	*get_next_line(int fd)
{
	static char	*residue;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	result = read_fd(fd, buffer, residue);
	free(buffer);
	buffer = NULL;
	if (!result)
		return (0);
	residue = recover_residue(result);
	return (result);
}
