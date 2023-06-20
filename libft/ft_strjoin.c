/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:30:17 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/05 19:18:23 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (0);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(size * sizeof(char));
	if (str == NULL)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin_1(char *s1, char *s2)
{
	char	*s3;
	size_t	total;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	s3 = ft_calloc(1, sizeof(char));
	total = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (s1)
		ft_strlcat(s3, s1, total);
	ft_strlcat(s3, s2, total);
	free((char *)s1);
	return (s3);
}

/*#include <stdio.h>
int	main(void)
{
	const char	s1[] = "ola";
	const char	s2[] = "adeus";

	printf("Nova string:%s", ft_strjoin(s1, s2));
	return (0);
}*/
