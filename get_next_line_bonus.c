/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:31:12 by ameskine          #+#    #+#             */
/*   Updated: 2024/12/20 10:59:05 by ameskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	get_line(int fd, char **s)
{
	char	*buffer;
	ssize_t	k;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	while (1)
	{
		k = read(fd, buffer, BUFFER_SIZE);
		if (k == -1)
			break ;
		if (k == 0)
			break ;
		buffer[k] = '\0';
		temp = ft_strjoin(*s, buffer);
		free(*s);
		*s = temp;
		if (!*s || ft_strchr(*s, '\n'))
			break ;
	}
	free(buffer);
}

char	*line_split(char **s)
{
	char	*g;
	char	*temp;
	char	*extracted_line;

	if (!*s || !**s)
		return (NULL);
	g = ft_strchr(*s, '\n');
	if (g)
	{
		extracted_line = ft_substr(*s, 0, g - *s + 1);
		temp = *s;
		*s = ft_substr(g + 1, 0, ft_strlen(g + 1));
		free(temp);
	}
	else
	{
		extracted_line = ft_substr(*s, 0, ft_strlen(*s));
		free(*s);
		*s = NULL;
	}
	return (extracted_line);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*d;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!s[fd])
	{
		s[fd] = malloc(1);
		if (!s[fd])
			return (NULL);
		s[fd][0] = '\0';
	}
	get_line(fd, &s[fd]);
	d = line_split(&s[fd]);
	if (!d)
	{
		free(s[fd]);
		s[fd] = NULL;
	}
	return (d);
}
