/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartins <lmartins@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 02:14:58 by lmartins          #+#    #+#             */
/*   Updated: 2021/01/17 23:41:06 by lmartins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*string;

	if (!(s1))
		return (ft_strdup(s2));
	if (!(string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		string[i] = s2[j];
		j++;
		i++;
	}
	string[i] = '\0';
	return (string);
}

void	ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

int		get_line(char **str, char **line, int ret)
{
	int		i;
	char	*temp;

	if (ret < 0)
		return (-1);
	else if (ret == 0 && *str[0] == '\0')
	{
		*line = ft_strdup("");
		ft_strdel(str);
		return (0);
	}
	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	*line = ft_substr(*str, 0, i);
	if ((*str)[i] == '\n')
	{
		temp = ft_strdup(*str + i + 1);
		free(*str);
		*str = temp;
		return (1);
	}
	ft_strdel(str);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				ret;
	static char		*str[OPEN_MAX];
	char			*buffer;
	char			*temp;

	if (BUFFER_SIZE < 1 || !line || fd < 0)
		return (-1);
	if (!(str[fd]))
		if (!(str[fd] = ft_strdup("")))
			return (-1);
	if (!(buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer))))
		return (-1);
	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		temp = ft_join(str[fd], buffer);
		ft_strdel(&str[fd]);
		str[fd] = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (get_line(&(str[fd]), line, ret));
}
