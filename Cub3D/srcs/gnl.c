/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahkalama <@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:19:36 by ahkalama          #+#    #+#             */
/*   Updated: 2024/02/08 14:19:37 by ahkalama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*ft_strchsr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_read_left_to_right(int fd, char *d_line)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchsr(d_line, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		d_line = ft_strsjoin(d_line, buff);
	}
	free(buff);
	return (d_line);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*d_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	d_line = ft_read_left_to_right(fd, d_line);
	if (!d_line)
		return (NULL);
	current_line = ft_get_line(d_line);
	d_line = ft_new_dinamic_line(d_line);
	return (current_line);
}
