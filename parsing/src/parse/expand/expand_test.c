/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 02:30:45 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/09 00:38:35 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


void remove_quotes(char *str, char c)
{
    int i;
    int j;
    int inside_quotes = 0;
    
    i = 0;
    j = 0;
    while (str[i]) 
    {
        if (str[i] == '\"')
        {
            inside_quotes = !inside_quotes;
        }
        if (str[i] == c && !inside_quotes)
        {
            i++;
            continue;
        }
        str[j++] = str[i++];
    }
    str[j] = '\0';
}

char *remove_single_quotes(char *str)
{
    char *new_str = malloc(strlen(str) + 1); // allocate memory for new string
    int in_double_quotes = 0; // flag to track if current character is inside double quotes
    int j = 0; // index for new string

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '"') {
            in_double_quotes = !in_double_quotes; // toggle flag
        } else if (str[i] == '\'' && !in_double_quotes) {
            continue; // skip single quotes that are not inside double quotes
        }
        new_str[j++] = str[i];
    }
    new_str[j] = '\0'; // terminate new string with null character
    return new_str;
}


void remove_double_quotes_inside_single_quotes(char *str, char c)
{
    int i;
    int j;
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;
    
    i = 0;
    j = 0;
    while (str[i]) 
    {
        if (str[i] == '\'')
        {
            inside_single_quotes = !inside_single_quotes;
        }
        else if (str[i] == '\"' && !inside_single_quotes)
        {
            inside_double_quotes = !inside_double_quotes;
        }
        if (str[i] == c && !inside_single_quotes && !inside_double_quotes)
        {
            i++;
            continue;
        }
        str[j++] = str[i++];
    }
    str[j] = '\0';
}

char	*expand_env(char	*dollar)
{
	int j = 0;
	char	*var_name;
	char	*var_value;
	char	*expanded = NULL;
	if (dollar[j++] == '?')
		expanded = ft_itoa(WEXITSTATUS(g_data.exit_status));
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


char *expand_cmd(char *str)
{
    int i;
    int count_single;
    int count_double;
    char *first = NULL;
    char *sec = NULL;
    int in_single_quotes = 0; // flag to track if current character is inside single quotes

    i = -1;
    count_single = 0;
    count_double = 0;
    while (str[++i])
    {
        if (str[i] == 39) // single quote encountered
            in_single_quotes = !in_single_quotes; // toggle flag
        if (str[i] == 34 && !in_single_quotes && (i == 0 || str[i - 1] != '\\')) // double quote encountered outside single quotes and not escaped
            count_double += 1;
        if (str[i] == '$' && !in_single_quotes && count_double % 2 != 0 ) // dollar sign encountered outside single quotes and inside an even number of double quotes
        {
            first = strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = ft_strjoin(first, sec);
            return (str);
        }
        if (str[i] == '$' && !in_single_quotes && count_double % 2 == 0) // dollar sign encountered outside single quotes and inside an even number of double quotes
        {
            first = strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = ft_strjoin(first, sec);
            return (str);
        }
    }
    return (str);
}

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
        else if (str[i] == 34 && single_quote % 2 == 2)
            double_quote += 1;
        if (str[i] == '$' && single_quote % 2 == 0)
        {
            first = ft_strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = ft_strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = ft_strjoin(first, sec);
            return (str);
        }
        else if (str[i + 1] == '$' && str[i] == 34 && single_quote % 2 == 0)
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
    int i;
    int double_quote;
    int single_quote;
    char *first;
    char *sec;
    
    i = -1;
    double_quote = 0;
    single_quote = 0;
    first = NULL;
    sec = NULL;

    while (str[++i])
    {
        if (str[i] == 34)
            double_quote += 1;
        if (str[i] == 39)
            single_quote += 1;
        if (str[i] == '$' && double_quote % 2 != 0 )
        {
            printf("test\n");
             first = strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = my_strjoin(first, sec);
            return (str);
        }
        if (str[i] == '$' && double_quote % 2 == 0 && single_quote % 2 == 0)
        {
            first = strndup(str, i);
            if (my_strcmp(str + i, "$") == 0)
                sec = strdup(str + i);
            else
                sec = expand_env(str + i + 1);
            str = ft_strjoin(first, sec);
            return (str);
        }
    }
    return (str);
}





char *expand_do(char *str)
{
	int u = 0;
	while (strchr(str, '$') && ++u < 11)
    {
		str = expand_cmd(str);
        // str = expand_cmd2(str);
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
        if (here_doc || temp->type != TOKEN_SINGLE_QUOTE || temp->type != TOKEN_DOUBLE_QUOTE)
        {
            temp->value = expand_do(temp->value);
            remove_double_quotes_inside_single_quotes(temp->value, 39);
            remove_quote(temp->value, 34);
            // remove_quotes(temp->value, 34);
        }
        if (temp->type == TOKEN_DOUBLE_QUOTE)
        {
            printf("hsm\n");
            temp->value = expand_double(temp->value);
            
            // remove_single_quotes(temp->value);
            remove_quotes(temp->value, 34);
        }
        if (temp->type == TOKEN_SINGLE_QUOTE)
        {
           expand_single(temp->value);
           remove_single_quotes(temp->value);
        //    remove_quote(temp->value, 39);
        }
        if (temp->type == TOKEN_HERE_DOC)
            here_doc = 0;
        else
            here_doc = 1;
        temp = temp->next;
    }
    return (*token);
}