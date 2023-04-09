/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:27:52 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/10 22:17:31 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

void    init_tokens(char *value, int type)
{
    t_tokens *tokens;

    tokens = malloc(sizeof(s_tokens));
    tokens->value = value;
    tokens->type = type;
    return (tokens);
}