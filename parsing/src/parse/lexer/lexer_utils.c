/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:11:40 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/14 20:09:26 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../../include/minishell.h"

//init_tokens
t_token *initialize_tokens(char *value, int type)
{
    t_token *token;

    if (!value)
        return (NULL);
    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

void add_token(t_token **token, int type, char *value, int i, int s)
{
    ft_add_back_token(token, initialize_tokens(ft_substr(value , s, i), type));
}

t_token *last_token(t_token *token)
{
    if (!token)
        return (NULL);
    while (token->next != NULL)
        token = token->next;
    return (token);
}


void ft_add_back_token(t_token **list_token, t_token *new_token)
{
    t_token *tmp;

    tmp = *list_token;
    if (!(*list_token))
        (*list_token) = new_token;
    else
    {
        tmp = last_token(*list_token);
        tmp->next = new_token;
    }
}

// int find_second_quote

// void token_skip_whitespace()
