/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaraujo <anaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:00:47 by marvin            #+#    #+#             */
/*   Updated: 2023/05/17 20:26:20 by anaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	char	*dst;

	if (!src)
		return (NULL);
	dst = malloc(ft_strlen(src) + 1);
	if (dst == NULL)
		return (0);
	ft_strcpy(dst, src);
	return (dst);
}

/*int main()
{
    char source[] = "GeeksForGeeks";
 
    // A copy of source is created dynamically
    // and pointer to copy is returned.
    char* target = strdup(source);
    char* target1 = ft_strdup(source);
 
    printf("%s\n", target);
    printf("%s", target1);
    return 0;
}*/
