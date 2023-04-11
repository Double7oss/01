/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:24 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/10 21:08:26 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <ctype.h>

#include "/Users/hel-kadd/Desktop/lastversion/minishell/execution.h"

typedef struct s_token {
    enum {
        TOKEN_STR,
        TOKEN_EQUALS,
        TOKEN_LESS,
        TOKEN_GREATER,
        TOKEN_GREATGREATER,
        TOKEN_PIPE,
        TOKEN_SEMI,
        TOKEN_GP,
        TOKEN_DP,
        TOKEN_RED_INFILE,
        TOKEN_RED_OUTFILE,
        TOKEN_AND,
        TOKEN_ENV,
        TOKEN_HERE_DOC,
        TOKEN_NEW_LINE,
        TOKEN_SINGLE_QUOTE,
        TOKEN_DOUBLE_QUOTE,
        TOKEN_APEND,
        TOKEN_DOLLAR,
    } type;
	char *value;
	struct s_token *next;
} t_token;

 
typedef struct s_argument {
    char *args;
    struct s_argument *next;
} t_args;

typedef struct s_var_quotes{
    int i;
    int double_quote;
    int single_quote;
    char *first;
    char *sec;
} t_var_quotes;

//token fuction
void ft_add_back_token(t_token **list_token, t_token *new_token);
t_token *initialize_tokens(char *value, int type);
void add_token(t_token **token, int type, char *value, int i, int s);
t_token *lexer(char *input);
int is_special_char(char c);
//str function for help parsing tokens
char	*ft_strchr(const char *s, int c);
char *ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//mem function for help parsing tokens
void	*ft_memcpy(void *dst, const void *src, size_t n);
//utils function
int is_charset(char c);
int is_whitespace(char c);
//parsing 
t_file *initialize_redirection(char *filename, char type);
t_exeuction *initialize_execution(char **str, t_file *file);
t_exeuction *last_exec(t_exeuction *exec);
void add_back_execution(t_exeuction **list_exec, t_exeuction *exec);
t_exeuction *simple_exec_cmd(t_token *token);
t_exeuction *filed_struct(char *input);
void		execution(t_exeuction *str);
void add_back_file(t_file **list_file, t_file *file);
t_token *expand_dollar(t_token **token1);
char *ft_getenv(char *cmd);
void rm_sng_quotes(t_token **head);
void rm_db_quotes(t_token **head);
char	*ft_itoa(int a);
int my_strcmp(const char *s1, const char *s2);
void remove_quote(char *str, char c);
#endif