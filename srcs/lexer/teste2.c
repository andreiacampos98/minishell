/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-f <csilva-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:17:55 by csilva-f          #+#    #+#             */
/*   Updated: 2023/06/11 15:21:07 by csilva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_null_str(void)
{
	char	*substr;

	substr = (char *)malloc(sizeof(char) * 1);
	if (substr == NULL)
		return (0);
	substr[0] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	size_t	j;
	char	*f;

	if (!s)
		return (0);
	lens = ft_strlen((char *)s);
	j = 0;
	if (len > lens)
		len = lens - start;
	if (lens < (size_t)start)
		return (ft_null_str());
	f = malloc(sizeof(char) * (len + 1));
	if (!f)
		return (NULL);
	while (j < len)
	{
		f[j] = s[start + j];
		j++;
	}
	f[j] = '\0';
	return (f);
}

int	ft_n_aspas(char *str, int *i)
{
	int		aa;
	char	c;
	int		n;

	aa = 0;
	c = '0';
	n = 0;
	while (str[++(*i)] != '\0')
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			if (aa && str[*i] == c)
			{
				aa = 0;
				n++;
			}
			else if (!aa)
			{
				n++;
				aa = 1;
				c = str[*i];
			}
		}
		else if (str[*i] == ' ' && !aa)
			break ;
	}
	return (n);
}

char	*ft_quotes_tk(char *str, int i)
{
	int 	aa;
	char	c;
	int		j;
	int		n;
	int		k;
	char	*str2;
	char	*tk;

	aa = 0;
	c = '0';
	j = 0;
	k = -1;
	n = ft_n_aspas(str, &i);
	str2 = ft_substr(str, 0, i);
	printf("str2: %s\n", str2);
	tk = malloc(sizeof(char) * (ft_strlen(str2) - n + 1));
	printf("i inicial: %d\nmalloc: %d\n", i, (int)ft_strlen(str2) - n + 1);
	i = -1;
	while (str2[++i])// && n % 2 == 0)
	{
		if ((str2[i] == '\"' || str2[i] == '\'') && (str2[i] == c || c == '0'))
		{
			if (aa && str2[i] == c)
			{
				aa = 0;
				c = '0';
			}
			else
			{
				k = j;
				aa = 1;
				c = str2[i];
			}
		}
		else
		{
			tk[j] = str2[i];
			j++;
		}
	}
	printf("i final: %d\n", i);
	i = -1;
	printf("tk_antes: %s\n", tk);
	printf("tk_len: %d\n", (int)ft_strlen(tk));
	if (c != '0' && aa)
	{
		printf("len: %d\n", (int)ft_strlen(tk));
		if (k < (int)ft_strlen(tk))
		{
			while (((int)ft_strlen(tk) - ++i) > k)
				tk[(int)ft_strlen(tk) - i] = tk[(int)ft_strlen(tk) - 1 - i];
		}
		tk[k] = c;
	}
	i = -1;
	printf("\n\ntk: ");
	while (tk[++i] != '\0')
		printf("%c", tk[i]);
	printf("\n\n");
	free(str2);
	return (tk);
}*/

/*int	main(void)
{
	int	i;

	i = -1;
	printf("n: %d\n", ft_n_aspas("\"\'l\'\"\"\'s-\'a\"", &i));
	i = -1;
	printf("n: %d\n", ft_n_aspas("\"\'l\"\'\"s-  a\"\'", &i));
	i = -1;
	printf("n: %d\n", ft_n_aspas("\"\"l\"\"\"s-a\"", &i));
	i = -1;
	printf("n: %d\n", ft_n_aspas("\"l\"\"\"s-a\"", &i));
	i = -1;
	printf("n: %d\n", ft_n_aspas("\"l\" \"s-a\"", &i));
	i = -1;
	printf("n: %d\n", ft_n_aspas("\"\"l\"\"   \"s-a\"", &i));
	return (0);
}

int	main(void)
{
	printf("1n: %s\n", ft_quotes_tk("\"\'l\'\"\"\'s-\'a\"", -1));
	printf("2n: %s\n", ft_quotes_tk("\"\'l\"\'\"s-  a\"\'", -1));
	printf("3n: %s\n", ft_quotes_tk("\"\'\"l\"\'\"\"s-a", -1));
	printf("4n: %s\n", ft_quotes_tk("\"l\"\"\"s-a\"", -1));
	printf("5n: %s\n", ft_quotes_tk("\"l\" \"s-a\"", -1));
	printf("6n: %s\n", ft_quotes_tk("\"\"l\"\"   \"s-a\"", -1));
	printf("7n: %s\n", ft_quotes_tk("\"\'l\'\"\'s-\'a\"", -1));
	printf("8n: %s\n", ft_quotes_tk("\"ls\'\"", -1));
	printf("9n: %s\n", ft_quotes_tk("\"ls", -1));
	printf("10n: %s\n", ft_quotes_tk("ls\'            \'ls", -1));
	printf("11n: %s\n", ft_quotes_tk("ls -l -a", -1));
	return (0);
}*/
