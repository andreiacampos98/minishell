/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:09:25 by anaraujo          #+#    #+#             */
/*   Updated: 2023/06/05 19:18:05 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr_1(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_read(int fd, char *str)
{
	char	*read_file;
	int		bytes;

	read_file = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	bytes = 1;
	if (!read_file)
		return (NULL);
	while (bytes != 0 && ft_strchr_1(str, '\n') == 0)
	{
		bytes = read(fd, read_file, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(read_file);
			return (NULL);
		}
		read_file[bytes] = '\0';
		str = ft_strjoin_1(str, read_file);
	}
	free(read_file);
	return (str);
}

char	*ft_read_line(char *read_file)
{
	char	*line;
	int		i;

	i = 0;
	if (!read_file[i])
		return (NULL);
	while (read_file[i] != '\n' && read_file[i] != '\0')
	{
		i++;
	}
	line = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (read_file[i] != '\0')
	{
		line[i] = read_file[i];
		i++;
		if (read_file[i - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_str_without_line(char *read_file)
{
	char	*without_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!read_file)
		return (NULL);
	while (read_file[i] != '\n' && read_file[i] != '\0')
		i++;
	if (read_file[i] == '\0')
	{
		free(read_file);
		return (NULL);
	}
	without_line = malloc(sizeof(char) * (ft_strlen(read_file) - i + 1));
	i++;
	while (read_file[i] != '\0')
		without_line[j++] = read_file[i++];
	without_line[j] = '\0';
	free(read_file);
	return (without_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	read = ft_read(fd, read);
	if (!read)
	{
		return (NULL);
	}
	line = ft_read_line(read);
	read = ft_str_without_line(read);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("teste", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/