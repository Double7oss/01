/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:44:12 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/09 02:14:16 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t  ft_strlen(const char *str)
{
	unsigned int	i;


	i = 0;
	while (str && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int ft_is_digit(char c)
{
    if (c >='0' && c <='9')
        return(1);
    return (0);
}

int     ft_isalpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    return (0);
}

int is_whitespace(char c)
{
    if (c == ' ' || (c >= 9 && c <= 13))
        return (0);
    return (1);
}

int is_special_char(char c)
{
    if (!ft_strchr("><|; ", c))
        return (1);
    return (0);
}

int ft_redirection(t_token *token)
{
    if (token->value[0] != '<' && token->value[0] != '>')
        return (0);
    return (1);
}

int is_charset(char c)
{
    if (c == 39 || c == 34 || c == '<' || c == '>' || c == '|'
		|| c == '$' || is_whitespace(c) || c == '\n' || c == '\0')
        return (1);
    return (0);
}

int find_second_quote(char *line, int i, int *nb_q, int q)
{
    int a;

    a = 0;
    a = i + 1;
    *nb_q += 1;
    while (line[a] && line[a] != q)
        a++;
    if (line[a] == q)
        *nb_q += 1;
    return (a - i);
}