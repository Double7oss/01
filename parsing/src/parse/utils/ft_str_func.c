/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:36:40 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/08 20:16:41 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
//BY ANAS . CHECK LINE 33
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strnlen(const char *str, size_t len)
{
	size_t	i; // THIS MESSAGE BY ANAS . RAH BDELT "INT I" L "SIZE_T I" KAN KAYTL3 ERROR
 
	i = 0;
	while (str[i] != '\0' && i < len)
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
void	ft_bzero(void *s, size_t n)
{
	char	*c;
	size_t	i;

	c = (char *)s;
	i = 0;
	while (i < n)
	{
		c[i] = '\0';
		i++;
	}
}
char *ft_strndup(const char *s, size_t n)
{
    size_t len;
	char *copy;

    len = ft_strnlen(s, n);
    copy = malloc(len + 1);
    if (copy == NULL)
        return (NULL);
    ft_memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c;

	c = (void *)malloc(nmemb * size);
	if (!c)
		return (NULL);
	ft_bzero(c, nmemb * size);
	return (c);
}
char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*str;

	i = ft_strlen(src);
	str = (char *)ft_calloc(sizeof(char) * (i + 1), 1);
	if (!str)
	{
		return (0);
	}
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		lenth;
	int		lenth2;
	char	*ptr;

	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(str1)+ ft_strlen(str2) + 1));
	if (ptr == NULL)
		return (NULL);
	lenth = 0;
	lenth2 = 0;
	while (str1 && str1[lenth] != '\0')
	{
		ptr[lenth] = str1[lenth];
		lenth++;
	}
	while (str2 && str2[lenth2] != '\0')
	{
		ptr[lenth] = str2[lenth2];
		lenth++;
		lenth2++;
	}
	ptr[lenth] = '\0';
	return (ptr);
}





char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}