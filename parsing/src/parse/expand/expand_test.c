/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:30:45 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/12 00:37:57 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"



void remove_quotes23(char *str) {
    int len = strlen(str);
    int i = 0;
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;

    while (i < len) {
        if (str[i] == '"' && !inside_single_quotes) {
            inside_double_quotes = !inside_double_quotes;
            i++;
        } else if (str[i] == '\'' && !inside_double_quotes) {
            inside_single_quotes = !inside_single_quotes;
            i++;
        } else if (str[i] == '"' && inside_single_quotes) {
            i++;
        } else if (str[i] == '\'' && inside_double_quotes) {
            i++;
        } else {
            i++;
        }
    }
    int j = 0;
    for (i = 0; i < len; i++) {
        if (str[i] == '"' && !inside_single_quotes) {
            inside_double_quotes = !inside_double_quotes;
        } else if (str[i] == '\'' && !inside_double_quotes) {
            inside_single_quotes = !inside_single_quotes;
        } else if (str[i] == '"' && inside_single_quotes) {
            str[j++] = '"';
        } else if (str[i] == '\'' && inside_double_quotes) {
            str[j++] = '\'';
        } else {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}



void handle_quotes(char *str) {
    int len = strlen(str);
    int i = 0;
    int inside_quotes = 0;
    char quote_type;
    while (i < len) {
        if ((str[i] == '\'' || str[i] == '\"') && !inside_quotes) {
            inside_quotes = 1;
            quote_type = str[i];
            i++;
        } else if (str[i] == quote_type && inside_quotes) {
            inside_quotes = 0;
            i++;
        } else {
            i++;
        }
    }
}

void remove_single_quotes(char *str) {
    int len = strlen(str);
    int i = 0;
    int inside_double_quotes = 0;
    while (i < len) {
        if (str[i] == '"' && !inside_double_quotes) {
            inside_double_quotes = 1;
            i++;
        } else if (str[i] == '"' && inside_double_quotes) {
            inside_double_quotes = 0;
            i++;
        } else if (str[i] == '\'' && !inside_double_quotes) {
            if (len > 1) {
                int j;
                for (j = i; j < len - 1; j++) {
                    str[j] = str[j + 1];
                }
                str[len - 1] = '\0';
                len--;
            } else {
                str[0] = '\0';
                len = 0;
            }
        } else {
            i++;
        }
    }
    if (len > 0 && str[len - 1] == '\'') {
        str[len - 1] = '\0';
    }
}


void remove_double_quotes(char *str)
{
    int len = strlen(str);
    int i = 0;
    int inside_single_quotes = 0;
    while (i < len) {
        if (str[i] == '\'' && !inside_single_quotes) {
            inside_single_quotes = 1;
            i++;
        } else if (str[i] == '\'' && inside_single_quotes) {
            inside_single_quotes = 0;
            i++;
        } else if (str[i] == '\"' && !inside_single_quotes) {
            int j;
            for (j = i; j < len - 1; j++) {
                str[j] = str[j + 1];
            }
            str[len - 1] = '\0';
            len--;
        } else {
            i++;
        }
    }
    if (len > 0 && str[len - 1] == '\"') {
        str[len - 1] = '\0';
    }
}



char	*expand_env(char	*dollar)
{
	int j = 0;
	char	*var_name;
	char	*var_value;
	char	*expanded = NULL;
	if (dollar[j++] == '?')
		expanded = ft_itoa(g_data.exit_status);
	else
	{
		while (dollar[j] && (dollar[j] == '_' || isdigit(dollar[j]) || isalpha(dollar[j])))
			j++;
		var_name = strndup(dollar, j);
		var_value = ft_getenv(var_name);
		if (var_value)
			expanded = strdup(var_value);
	}
	expanded = ft_strjoin(expanded, dollar + j);
	return (expanded);
}


// char *expand_cmd(char *str)
// {
//     int i;
//     int count_single;
//     int count_double;
//     char *first = NULL;
//     char *sec = NULL;
//     int in_single_quotes = 0; // flag to track if current character is inside single quotes

//     i = -1;
//     count_single = 0;
//     count_double = 0;
//     while (str[++i])
//     {
//         if (str[i] == 39) // single quote encountered
//             in_single_quotes = !in_single_quotes; // toggle flag
//         if (str[i] == 34 && !in_single_quotes && (i == 0 || str[i - 1] != '\\')) // double quote encountered outside single quotes and not escaped
//             count_double += 1;
//         if (str[i] == '$' && !in_single_quotes && count_double % 2 != 0 ) // dollar sign encountered outside single quotes and inside an even number of double quotes
//         {
//             first = strndup(str, i);
//             if (my_strcmp(str + i, "$") == 0)
//                 sec = strdup(str + i);
//             else
//                 sec = expand_env(str + i + 1);
//             str = ft_strjoin(first, sec);
//             return (str);
//         }
//         if (str[i] == '$' && !in_single_quotes && count_double % 2 == 0) // dollar sign encountered outside single quotes and inside an even number of double quotes
//         {
//             first = strndup(str, i);
//             if (my_strcmp(str + i, "$") == 0)
//                 sec = strdup(str + i);
//             else
//                 sec = expand_env(str + i + 1);
//             str = ft_strjoin(first, sec);
//             return (str);
//         }
//     }
//     return (str);
// }


char *expand_single(char *str)
{
    int i;
    int single_quote;
    int double_quote;
    char *first;
    char *sec;

    i = -1;
    single_quote = 0;
    double_quote = 0;
    first = NULL;
    sec = NULL;
    while (str[++i])
    {
        if (str[i] == 39)
            single_quote += 1;
        else if (str[i] == 34 && single_quote % 2 == 0)
            double_quote += 1;
        if (str[i] == '$' && single_quote % 2 == 0 && double_quote % 2 != 0)
        {
            first = ft_strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = ft_strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = ft_strjoin(first, sec);
            return (str);
        }
    }
    return (str);
}



char *expand_double(char *str)
{
    t_var_quotes var;
    
    var.i = -1;
    var.double_quote = 0;
    var.single_quote = 0;
    var.first = NULL;
    var.sec = NULL;

    while (str[++var.i])
    {
        if (str[var.i] == 34)
            var.double_quote += 1;
        if (str[var.i] == 39)
            var.single_quote += 1;
        if (str[var.i] == '$' && (var.double_quote % 2 != 0 || (var.double_quote % 2 == 0 && var.single_quote % 2 == 0)))
        {
            var.first = ft_strndup(str, var.i);
            if (my_strcmp(str + var.i, "$") == 0)
                var.sec = ft_strdup(str + var.i);
            else
                var.sec = expand_env(str + var.i + 1);
            str = my_strjoin(var.first, var.sec);
            return (str);
        }
    }
    return (str);
}

int check_space(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
    {
        if (str[i] == ' ')
            return (0);
        i++;
    }
    return (1);
}

int count_dollar(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '$')
            count++;
        i++;
    }
    return (count);
    
}

char *expand_do(char *str)
{
	int u;

    u = count_dollar(str);
	while (strchr(str, '$') && u >= 0)
    {
		str = expand_double(str);
        u--;
    }
	return(str);
}

char *expand_sq(char *str)
{
    int u;

    u = count_dollar(str);
	while (strchr(str, '$') && u-- >= 0)
    {
		str = expand_single(str);
    }
	return(str);
}


t_token *expand_dollar(t_token **token)
{
    t_token *temp;
    int here_doc;
    
    here_doc = 0;
    temp = (*token);
    while (temp)
    {
        if (here_doc && temp->type != TOKEN_SINGLE_QUOTE && temp->type != TOKEN_DOUBLE_QUOTE)
        {
            temp->value = expand_do(temp->value);
            remove_quotes23(temp->value);
        }
        if (temp->type == TOKEN_DOUBLE_QUOTE)
        {
            temp->value = expand_do(temp->value);
            remove_quotes23(temp->value);
        }
        if (temp->type == TOKEN_SINGLE_QUOTE)
        {
            temp->value = expand_do(temp->value);
            remove_quotes23(temp->value);
        }
        if (temp->type == TOKEN_HERE_DOC)
            here_doc = 0;
        else
            here_doc = 1;
        temp = temp->next;
    }
    return (*token);
}