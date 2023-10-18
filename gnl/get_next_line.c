/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:47:41 by anollero          #+#    #+#             */
/*   Updated: 2023/10/04 13:14:42 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*join;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(len);
	if (join == 0)
		return (0);
	ft_bzero(join, len);
	ft_strlcpy(join, s1, len);
	ft_strlcpy((join + ft_strlen(s1)), s2, len);
	return (join);
}

char	*ft_clearbuff(char **nl)
{
	char	*ret;
	char	*temp;
	int		count;

	count = 0;
	while ((*nl)[count] != '\0' && (*nl)[count] != '\n')
		count++;
	if ((*nl)[count] == '\n')
		count++;
	ret = malloc(count + 1);
	ft_strlcpy(ret, *nl, count + 1);
	temp = ft_strdup(*nl + count);
	free(*nl);
	*nl = temp;
	return (ret);
}

void	ft_join_two_buffers(char *buff, int ret, char **nl)
{
	char	*temp;

	buff[ret] = '\0';
	temp = ft_strjoin(*nl, buff);
	free(*nl);
	*nl = temp;
}

char	*get_next_line(int fd)
{
	int			ret;
	char		buff[BUFFER_SIZE + 1];
	static char	*nl;

	ret = 1;
	ft_bzero(buff, BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (nl == NULL)
			nl = ft_strdup(buff);
		else if (ret > 0)
			ft_join_two_buffers(buff, ret, &nl);
		if ((nl[0] == '\0' && ret == 0) || ret < 0)
		{
			free(nl);
			nl = NULL;
			return (NULL);
		}
		if (ft_strnchr(nl, '\n'))
			break ;
	}
	return (ft_clearbuff(&nl));
}
