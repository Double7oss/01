/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:25:38 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/12 00:31:34 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int db_condition(char *input, int i, int count, int x)
{
	while (input[i] != '\0')
	{
		if (input[i] == 34)
			count++;
		if (input[i] == 39 && count % 2 == 0)
			x++;
		if ((input[i] == 34 && input[i + 1] == ' '))
		{
			i++;
			break ;
		}
		if (input[i] == ' ' && count % 2 == 0 && x % 2 == 0)
			break ;
		i++;
	}
	if ((count % 2 != 0 && x % 2 == 0) || (x % 2 != 0 && count % 2 == 0))
	{
		printf("quotes not closed\n");
		return (-1);
	}
	return (i);
}
int sq_condition(char *input, int i, int count, int x)
{
		while (input[i] != '\0')
	{
		if (input[i] == 34 && count % 2 == 0)
			x++;
		if (input[i] == 39)
			count++;
		if (input[i] == 39 && (input[i + 1] == ' '))
		{
			i++;
			break ;
		}
		if (input[i] == ' ' && count % 2 == 0 && x % 2 == 0)
			break ;
		i++;
	}
	if ((count % 2 != 0 && x % 2 == 0) || (x % 2 != 0 && count % 2 == 0))
	{
		printf("quotes not closed\n");
		return (-1);
	}
	return (i);
}

