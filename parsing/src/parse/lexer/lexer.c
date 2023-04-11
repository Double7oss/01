/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:21:09 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/11 19:54:40 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	remove_quote(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		str[j++] = str[i++];
	}
	str[j] = '\0';
}

int	lexer_semi_pipe(t_token **token, int i, char *input)
{
	if (input[i] == ';')
		ft_add_back_token(token,
			initialize_tokens(ft_strndup(input + i, 1), TOKEN_SEMI));
	if (input[i] == '|')
		ft_add_back_token(token,
			initialize_tokens(ft_strndup(input + i, 1), TOKEN_PIPE));
	return (i);
}

int	lexer_redirection(t_token **token, int i, char *line)
{
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			ft_add_back_token(token, initialize_tokens
				(ft_strndup(line + i, 2), TOKEN_HERE_DOC));
			i++;
		}
		else
			ft_add_back_token(token,
				initialize_tokens(ft_strndup(line + i, 1), TOKEN_RED_INFILE));
	}
	else
	{
		if (line[i + 1] == '>')
		{
			ft_add_back_token(token,
				initialize_tokens(ft_strndup(line + i, 2), TOKEN_APEND));
			i++;
		}
		else
			ft_add_back_token(token,
				initialize_tokens(ft_strndup(line + i, 1), TOKEN_RED_OUTFILE));
	}
	return (i);
}

int	lexer_is_word(t_token **token, char *input, int i, int s)
{
	int	count;
	int	single;

	s = i;
	count = 0;
	single = 0;
	while (input[i])
	{
		if (input[i] == 39 && count % 2 == 0)
			single++;
		if (input[i] == 34 && single % 2 == 0)
			count++;
		if (is_special_char(input[i]) == 0 && count % 2 == 0)
			break ;
		i++;
	}
	if ((count % 2 != 0 && single % 2 == 0)
		|| (count % 2 == 0 && single % 2 != 0))
	{
		printf("quotes not closed\n");
		return (-1);
	}
	add_token(token, TOKEN_STR, input, i - s, s);
	return (i);
}

int	double_quotes(t_token **token, char *input, int i, int s)
{
	int	count;
	int	x;

	s = i;
	i += 1;
	count = 1;
	x = 0;
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
	ft_add_back_token(token,
		initialize_tokens(ft_strndup(input + s, i - s), TOKEN_DOUBLE_QUOTE));
	return (i);
}

int	single_quotes(t_token **token, char *input, int i, int s)
{
	int	count;
	int	x;

	s = i;
	count = 1;
	i += 1;
	x = 0;
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
	if (count % 2 != 0 || (x % 2 != 0 && count % 2 == 0))
	{
		printf("quotes not closed\n");
		return (-1);
	}
	ft_add_back_token(token,
		initialize_tokens(ft_strndup(input + s, i - s), TOKEN_SINGLE_QUOTE));
	return (i);
}

void	rm_db_quotes(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	while (tmp)
	{
		if (tmp->type == TOKEN_DOUBLE_QUOTE || tmp->type == TOKEN_STR)
			remove_quote(tmp->value, 34);
		tmp = tmp->next;
	}
}

void	rm_sng_quotes(t_token **head)
{
	t_token	*tmp;

	tmp = (*head);
	while (tmp)
	{
		if (tmp->type == TOKEN_SINGLE_QUOTE || tmp->type == TOKEN_STR)
			remove_quote(tmp->value, 39);
		tmp = tmp->next;
	}
}

t_token	*lexer(char *input)
{
	t_token	*head;
	int		i;
	int		s;

	i = 0;
	head = NULL;
	s = i;
	while (input[i])
	{
		if (is_charset(input[i]) != 0 && input[i] != 34 && input[i] != 39
			&& input[i] != ' ' && input[i] != '|' && input[i] != '<'
			&& input[i] != '>' && input[i] != ';')
		{
			i = lexer_is_word(&head, input, i, s);
			if (i == -1)
				return (NULL);
		}
		else if (input[i] == 39)
		{
			i = single_quotes(&head, input, i, s);
			if (i == -1)
				return (NULL);
		}
		if (input[i] == 34)
		{
			i = double_quotes(&head, input, i, s);
			if (i == -1)
				return (NULL);
		}
		if ((input[i] == '|' || input[i] == ';') && input[i] != ' ')
			i = lexer_semi_pipe(&head, i, input);
		if ((input[i] == '<' || input[i] == '>'))
			i = lexer_redirection(&head, i, input);
		i++;
	}
	return (head);
}
