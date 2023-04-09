/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 20:36:07 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/06 20:55:12 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int check_for_dollar(char* str) {
    int in_single_quotes = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        if (str[i] == '\'') {
            in_single_quotes = !in_single_quotes; // toggle the flag
        } else if (in_single_quotes && str[i] == '$') {
            return 1;
        }
        
        i++;
    }
    
    return 0;
}

static int	ft_number_lenth(int a)
{
	int	x;

	x = 0;
	if (a == 0)
	{
		return (1);
	}
	if (a < 0)
	{
		a = a * -1;
		x++;
	}
	while (a > 0)
	{
		a = a / 10;
		x++;
	}
	return (x);
}

static void	helper_function(char *str, int a, int x)
{
	if (a < 0)
	{
		str[0] = '-';
		a = a * -1;
	}
	if (a == 0)
	{
		str[0] = '0';
	}
	while (a > 0)
	{
		str[x] = (a % 10) + '0';
		x--;
		a = a / 10;
	}
}

char	*ft_itoa(int a)
{
	int		x;
	char	*str;

	if (a == -2147483648)
		return (ft_strdup("-2147483648"));
	x = ft_number_lenth(a);
	str = (char *)malloc(sizeof(char) * (x + 1));
	if (str == NULL)
		return (NULL);
	str[x] = '\0';
	x--;
	helper_function(str, a, x);
	return (str);
}

int check_dollar(char *str)
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

void replaceSubstring(char **str, const char *oldSubstr, const char *newSubstr) {
	int oldSubstrLen = strlen(oldSubstr);
	int newSubstrLen = strlen(newSubstr);
	char *pos = *str;
	char *temp = NULL;
	char *temp_pos = NULL;
	
	while ((pos = strstr(pos, oldSubstr)) != NULL) {
		// Allocate a temporary buffer to hold the modified string
		temp = (char*)malloc(strlen(*str) + newSubstrLen - oldSubstrLen + 1);
		if (temp == NULL) {
			fprintf(stderr, "Failed to allocate memory for temporary buffer\n");
			return;
		}
		
		// Copy characters from start of string up to the position of the old substring
		temp_pos = strncpy(temp, *str, pos - *str);
		temp_pos += pos - *str;
		
		// Copy the new substring into the temporary buffer
		temp_pos = strncpy(temp_pos, newSubstr, newSubstrLen);
		temp_pos += newSubstrLen;
		
		// Copy any remaining characters from the original string into the temporary buffer
		strcpy(temp_pos, pos + oldSubstrLen);
		
		// Free the original string
		free(*str);
		
		// Update the original string pointer to point to the temporary buffer
		*str = temp;
		
		// Update the position pointer to point to the next character after the old substring
		pos += newSubstrLen;
	}
}



char *get_substring(char *str) {
    char *ptr = strstr(str, "$");
    if (ptr != NULL) {
        char *start = ptr + 1;
        char *end = start;
        while (*end != '\0' && ft_isalnum(*end)) {
            end++;
        }
        size_t len = end - start;
        char *sub_str = (char*)malloc(len + 1);
        if (sub_str != NULL) {
            strncpy(sub_str, start, len);
            sub_str[len] = '\0';
            return sub_str;
        }
    }
    return NULL;
}





// char *replace_env_variables_single_quote(char *str)
// {
//     char *new_str = strdup(str); // make a copy of the input string
//     char *dollar_sign = strchr(new_str, '$'); // find the first occurrence of '$'
//     while (dollar_sign != NULL)
//     {
//         char *env_value = NULL;
//         if (*(dollar_sign + 1) != '\0' && *(dollar_sign + 1) != '$') // check if there is an environment variable name after '$'
//         {
//             char *env_var = dollar_sign + 1; // get the environment variable name
//             env_value = ft_getenv(env_var); // get the environment variable value
//             if (env_value == NULL && *(dollar_sign + 2) == '?')
//             {
//                 // if the environment variable name is "$?" and it doesn't have a value, use the exit status variable
//                 char *exit_status_str = ft_itoa(g_data.exit_status);
//                 env_value = strdup(exit_status_str);
//                 free(exit_status_str);
//             }
//         }
//         else
//         {
//             env_value = strdup("$"); // if there is no environment variable name, add "$" to the output string
//         }

//         // replace the substring with the environment variable value
//         char *new_sub_str = ft_strjoin(ft_substr(new_str, 0, dollar_sign - new_str), env_value);
//         char *end = dollar_sign + (env_value == NULL ? 1 : strlen(env_value) + 1); // skip the environment variable name
//         new_str = ft_strjoin(new_sub_str, ft_substr(new_str, end - new_str, strlen(new_str)));
//         free(new_sub_str);

//         if (env_value != NULL)
//         {
//             free(env_value);
//         }

//         dollar_sign = strchr(new_str, '$'); // find the next occurrence of '$'
//     }
//     return new_str;
// }



char *replace_env_variables(char *str)
{
    char *new_str = strdup(str); // make a copy of the input string
    char *dollar_sign = strchr(new_str, '$'); // find the first occurrence of '$'
    while (dollar_sign != NULL)
    {
        char *env_var = get_substring(dollar_sign); // get the environment variable name
        if (env_var != NULL)
        {
            char *env_value = ft_getenv(env_var); // get the environment variable value
            if (env_value != NULL)
            {
                // replace the substring with the environment variable value
                char *new_sub_str = ft_strjoin(ft_substr(new_str, 0, dollar_sign - new_str), env_value);
                char *end = dollar_sign + strlen(env_var) + 1; // skip the environment variable name
                new_str = ft_strjoin(new_sub_str, ft_substr(new_str, end - new_str, strlen(new_str)));
                free(new_sub_str);
            }
            else if (*(dollar_sign + 1) == '?')
            {
				//g_data.exit_status = 1;
                // replace the substring with the exit status variable value
                char *exit_status_str;
              exit_status_str  =ft_itoa(g_data.exit_status);
                char *new_sub_str = ft_strjoin(ft_substr(new_str, 0, dollar_sign - new_str), exit_status_str);
                char *end = dollar_sign + 2; // skip the environment variable name
                new_str = ft_strjoin(new_sub_str, ft_substr(new_str, end - new_str, strlen(new_str)));
                free(new_sub_str);
            }
            else
            {
                // replace the substring with an empty string
                char *new_sub_str = ft_substr(new_str, 0, dollar_sign - new_str);
                char *end = dollar_sign + strlen(env_var) + 1; // skip the environment variable name
                new_str = ft_strjoin(new_sub_str, ft_substr(new_str, end - new_str, strlen(new_str)));
                free(new_sub_str);
            }
            free(env_var);
            dollar_sign = strchr(new_str, '$'); // find the next occurrence of '$'
        }
        else
        {
            break;
        }
    }
    return new_str;
}
char *get_single_quoted_string(char *str) {
    char *start = strchr(str, '\''); // find the first single quote
    if (start == NULL) {
        return NULL; // no single quotes found
    }
    char *end = strchr(start + 1, '\''); // find the second single quote
    if (end == NULL) {
        return NULL; // no closing single quote found
    }
    char *result = (char*) malloc(end - start); // allocate memory for the result
    strncpy(result, start + 1, end - start - 1); // copy the substring
    result[end - start - 1] = '\0'; // null terminate the result
    return result;
}

char* get_env_variable(char* str) {
    int i = 0;
    int len = strlen(str);
    int in_quotes = 0; // 0 means not inside quotes, 1 means inside single quotes, 2 means inside double quotes
    char* env_var = NULL;
    char* result = NULL;

    while (i < len) {
        if (str[i] == '\'') {
            in_quotes = (in_quotes == 1) ? 0 : 1; // toggle between 0 and 1
        } else if (str[i] == '\"') {
            in_quotes = (in_quotes == 2) ? 0 : 2; // toggle between 0 and 2
        } else if (str[i] == '$' && in_quotes == 0) {
            env_var = &str[i+1];
            while (ft_isalnum(str[i+1])) {
                i++;
            }
            str[i+1] = '\0';
            result = getenv(env_var);
            break;
        }
        i++;
    }

    return result;
}



// void expand_dollar(t_token **token1)
// {
// 	t_token *token;

// 	token = (*token1);
// 	while (token)
// 	{
// 		if (check_dollar(token->value) >= 1)
// 		{
// 			// printf("type token [%d]\n", token->type);
// 			// printf("check_for_dollaer = %d\n",check_for_dollar(token->value));
//             if (token->type == TOKEN_SINGLE_QUOTE)
//             {
//                  token->value = ft_strjoin(get_single_quoted_string(token->value), get_env_variable(token->value));
//             }
//             if (token->type != TOKEN_SINGLE_QUOTE)
// 				token->value = replace_env_variables(token->value);
// 		}
// 		token = token->next;
// 	}
// }