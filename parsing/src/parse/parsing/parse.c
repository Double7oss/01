/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:32:59 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/09 21:39:59 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"



char check_type_of_file(int type)
{
	if (type == TOKEN_RED_OUTFILE)
		return ('O');
	if (type == TOKEN_RED_INFILE)
		return ('I');
	if (type == TOKEN_HERE_DOC)
		return ('H');
	if (type == TOKEN_APEND)
		return ('A');
	return ('N');
}

void *my_realloc(void *ptr, size_t size)
{
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        return calloc(size, 1);
    }
    void *new_ptr = calloc(size, 1);
    if (new_ptr == NULL) {
        return NULL;
    }
    size_t old_size = sizeof(*ptr);
    if (size > old_size) {
        size = old_size;
    }
    for (size_t i = 0; i < size; i++) {
        ((char *) new_ptr)[i] = ((char *) ptr)[i];
    }
    free(ptr);
    return new_ptr;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

// t_exeuction *filed_struct(char *input)
// {
// 	t_file *file;
// 	t_token *token;
// 	t_exeuction *exec;
// 	char type;
// 	int i;
// 	char **str;
	
// 	token = lexer(input);
// 	str = malloc(sizeof(char *));
// 	i = 0;
// 	str[i] = NULL;
// 	exec = NULL;
// 	file = NULL;
// 	while (token)
// 	{
// 		printf("hsm\n");
// 		if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
// 		{
// 			type = check_type_of_file(token->type);
// 			if (token->next != NULL)
// 			{
// 				token = token->next;
// 			}
// 			file = initialize_redirection(token->value, type);
// 			if (token->next != NULL)
// 			{
// 				token = token->next;
// 			}
// 		}
// 		else if (token->type != TOKEN_PIPE)
// 		{
// 			str = realloc(str, (i + 1) * sizeof(char *));
// 			str[i] = ft_strdup(token->value);
// 			i++;
// 		}
// 		else if (token->type == TOKEN_PIPE)
// 		{
// 			str = realloc(str, (i + 1) * sizeof(char *));
// 			str[i] = NULL;
// 			add_back_execution(&exec, initialize_execution(str, file));
// 			str = malloc(sizeof(char *));
// 			i = 0;
// 			str[i] = NULL;
// 		}
// 		// if (token && token->next != NULL)
// 			token = token->next;
// 	}
// 	return (exec);
// }


// t_exeuction *filed_struct(char *input)
// {
//     t_file *file = NULL;
//     t_token *token = lexer(input);
//     t_exeuction *exec = NULL;
//     char type;
//     int i = 0;
//     char **str = malloc(sizeof(char *));
//     str[0] = NULL;

//     while (token)
//     {
//         if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
//         {
//             type = check_type_of_file(token->type);
//             if (token->next != NULL && token->next->type == TOKEN_STR)
//             {
//                 token = token->next;
//                 file = initialize_redirection(token->value, type);
//             }
//         }
//         if (token->type != TOKEN_PIPE)
//         {
//             str = realloc(str, (i + 1) * sizeof(char *));
//             str[i] = ft_strdup(token->value);
//             i++;
//         }
//         else if (token->type == TOKEN_PIPE)
//         {
//             str = realloc(str, (i + 1) * sizeof(char *));
//             str[i] = NULL;
//             add_back_execution(&exec, initialize_execution(str, file));
//             file = NULL;
//             str = malloc(sizeof(char *));
//             i = 0;
//             str[i] = NULL;
//         }
//         token = token->next;
// 		printf("gfdgdfg\n");
//     }
//         str = realloc(str, (i + 1) * sizeof(char *));
//         str[i] = NULL;
//         add_back_execution(&exec, initialize_execution(str, file));
//     // free_token_list(token);
//     return (exec);
// }



























// t_token *filed_word(t_exeuction *exec, t_token *token, t_file *file)
// {
// 	char **str;
// 	int i;

// 	i = 0;
// 	str = malloc(sizeof(char *));
// 	str[0] = NULL;
// 	while (token && token->type != TOKEN_PIPE)
// 	{
// 		str = realloc(str, (i + 1) * sizeof(char *));
// 		str[i] = ft_strdup(token->value);
// 		i++;
// 		token = token->next;
// 	}
// 	str = realloc(str, (i + 1) * sizeof(char *));
// 	str[i] = NULL;
// 	add_back_execution(&exec, initialize_execution(str, file));
// 	printf("gg\n");
// 	return (token);
// }


// t_exeuction *simple_exec_cmd(t_token *token)
// {
// 	t_exeuction *smpl;
// 	t_file *file;
// 	char type;

// 	file = NULL;
// 	smpl = NULL;
// 	while (token)
// 	{
// 		if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
// 		{
// 			type = check_type_of_file(token->type);
// 			if (token->next != NULL && token->next->type == TOKEN_STR)
// 			{
// 				printf("test\n");
// 				token = token->next;
// 				file = initialize_redirection(token->value, type);
// 				if (token->next != NULL)
// 					token = token->next;
// 			}
// 		}
// 		token = filed_word(smpl,token,file);
// 		if (token && token->next != NULL)
// 			token = token->next;
// 	}
// 	return (smpl);
// }

// t_exeuction *filed_struct(char *input)
// {
// 	t_file *file;
// 	t_token *token;
// 	char **str;
// 	t_exeuction *exec;
// 	int i;
// 	char type;
	
// 	exec = NULL;
	
// 	token = lexer(input);
// 	while (token != NULL)
// 	{
// 		str = malloc(sizeof(char *));
// 		str[0] = NULL;
// 		file = NULL;
// 		i = 0;

// 		while (token != NULL && strcmp(token->value, "|") != 0)
// 		{
// 			if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
// 			{
// 				type = check_type_of_file(token->type);
// 				if (token->next != NULL && token->next->type == TOKEN_STR)
// 				{
// 					printf("test\n");
// 					token = token->next;
// 					file = initialize_redirection(token->value, type);
// 					if (token->next != NULL)
// 						token = token->next;
// 				}
// 			}
// 			else
// 			{
// 				str = realloc(str, (i + 1) * sizeof(char *));
// 				str[i] = ft_strdup(token->value);
// 				i++;
// 			}
// 			token = token->next;
// 		}
// 		str = realloc(str, (i + 1) * sizeof(char *));
// 		str[i] = NULL;
// 		add_back_execution(&exec, initialize_execution(str, file));
// 		if (token != NULL && strcmp(token->value, "|") == 0)
// 			token = token->next;
// 	}		
// 	return (exec);
// }



// t_token *is_red(t_execition **exec, t_token *token, char **str)
// {
	
// }
t_token *token_is_file(t_token *token, t_file **file)
{
    char type;

    type = check_type_of_file(token->type);
    if (token->next != NULL && token->next->type != TOKEN_PIPE)
        token = token->next;
    add_back_file(file,initialize_redirection(token->value, type));
        token = token->next;
    return (token);
}

t_token *token_in_string(t_exeuction **cmd, t_token *token)
{
    char **str = NULL;
    t_file *file = NULL;
    int i = 0;
    
    while (token != NULL && my_strcmp(token->value, "|") != 0)
    {
        if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
        {
            token = token_is_file(token, &file);
        }
        else
        {
            char **new_str = malloc(sizeof(char *) * (i + 2));
            if (new_str == NULL)
            {
                // handle error
                return NULL;
            }
            memcpy(new_str, str, sizeof(char *) * i);
            new_str[i] = strdup(token->value);
            new_str[i + 1] = NULL;
            free(str);
            str = new_str;
            i++;
            token = token->next;
        }
    }
    

    add_back_execution(cmd, initialize_execution(str, file));
    return token;
}


// t_token *token_in_string(t_exeuction **cmd, t_token *token)
// {
//     char **str;
//     t_file *file;
//     int i;
    
//     i = 0;
//     str = malloc(sizeof(char *));
//     str[i] = NULL;
//     file = NULL;
//     while (token != NULL && my_strcmp(token->value, "|") != 0)
//     {
//         if (token->type == TOKEN_HERE_DOC || token->type == TOKEN_RED_INFILE || token->type == TOKEN_RED_OUTFILE || token->type == TOKEN_APEND)
//         {
//             token = token_is_file(token, &file);
//         }
//         else
//         {
//             str = realloc(str,(i + 1) * sizeof(char *));
//             str[i] = strdup(token->value);
//             i++; 
//             token = token->next;
//         }
//     }
//     str = realloc(str, sizeof(char *) * (i + 1));
//     str[i] = NULL;
//     add_back_execution(cmd, initialize_execution(str, file));
//     return (token);
    
// }

int check_tokens(t_token *head) {
    t_token *curr = head;
    int i = 1; // Counter to keep track of the position of the current token

    while (curr) {
        if (curr->type == TOKEN_LESS || curr->type == TOKEN_GREATER || 
            curr->type == TOKEN_GREATGREATER || curr->type == TOKEN_PIPE ||
            curr->type == TOKEN_APEND || curr->type == TOKEN_RED_INFILE || curr->type == TOKEN_RED_OUTFILE || curr->type == TOKEN_SEMI) {
            if (curr->next && curr->next->type != TOKEN_DOUBLE_QUOTE) {
                if (curr->next->type == TOKEN_PIPE && i == 1) {
                    printf("bash: syntax error near unexpected token `%s'\n", curr->next->value);
                    g_data.exit_status = 258;
                    return (-1);
                }
                else if (curr->next->type != TOKEN_STR && curr->next->type != TOKEN_DOLLAR &&
                         curr->next->type != TOKEN_SINGLE_QUOTE) {
                    printf("bash: syntax error near unexpected token `%s'\n", curr->next->value);
                    g_data.exit_status = 258;
                    return (-1);
                }
            }
            else if (!curr->next) {
                printf("bash: syntax error near unexpected token `newline'\n");
                    g_data.exit_status = 258;
        
                return (-1);
            }
        }
        curr = curr->next;
        i++;
    }
    return 0;
}


int check_redirect_tokens(t_token *token_list)
{
    t_token *current_token = token_list;
    while (current_token != NULL) {
        if ((current_token->type == TOKEN_RED_INFILE ||
             current_token->type == TOKEN_RED_OUTFILE ||
             current_token->type == TOKEN_APEND) &&
            current_token->next != NULL &&
            current_token->next->value != NULL &&
            current_token->next->value[0] == '$' &&
            current_token->next->value[1] != '\0') {

            char *var_name = &(current_token->next->value[1]);
            char *var_value = ft_getenv(var_name);

            if (var_value == NULL || var_value[0] == '\0' ||
                strchr(var_value, ' ') != NULL) {
                ft_putstr_fd("mini: ambiguous redirect\n ", 2);
                return (-1);
            }
        }

        current_token = current_token->next;
    }
    return (0);
}

t_exeuction *filed_struct(char *input)
{
	t_token *token;
    t_exeuction *cmd;
    
    cmd = NULL;
    token = lexer(input);
    if (check_tokens(token) == -1)
        return NULL;
   if (check_redirect_tokens(token) == -1)
    return (NULL);
   token =  expand_dollar(&token);
    if (token == NULL)
        return NULL;
    // rm_db_quotes(&token);
    // rm_sng_quotes(&token);
    while (token)
    {
       // printf("test\n");
        if (my_strcmp(token->value, "|") != 0)
        {
            token = token_in_string(&cmd, token);
        
        }
        else
        {
            token = token->next;
        }
    }
    if (!cmd)
        return (NULL);
    return (cmd);
}