
#ifndef EXECUTION_H
#define EXECUTION_H

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
typedef struct s_variables
{
	int		i;
	int		k;
	int		**fd;
	int		size;
	int		count;
	pid_t	id;
	int		a;
	char	**cmd;
	char	*comd;
	char	**env;
}t_va;
typedef struct s_s
 {
 	struct s_s	*next;
 	char		*name;
 	char 		*value;
 }t_execute;
typedef struct s_data 
{
	int exit_status;
	int last_exit_status;
	t_execute *str;
}   t_data;


 typedef struct s_files
 {
	char	*name;
	int		fp;
	int		here_doc;
	char	type;
	struct	s_files *next;
 }t_file;
typedef struct  s_list
{
	char			**str;
	t_file			*file;
	char			**env;
	int				i;
	int				k;
	struct  s_list	*next;
}t_exeuction;

t_data  g_data;

void		fill_env(char **env);
char		*name_without_equal(char *str);
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int a);
size_t		my_strlen(const char *str);
char		*my_strdup(const char *s);
void		ft_putstr_fd(char *s, int fd);
int			my_lstsize(t_execute *lst);
t_execute	*my_lstnew(void *before, void *after);
char		*my_substr(char *str, unsigned int start, size_t len);
char		**ft_split(char *str, char cut);
char		*my_strjoin(char *str1, char *str2);
int			t_isalnum(int a);
t_execute	*my_lstlast(t_execute *lst);
void		my_lstadd_back(t_execute **lst, t_execute *new);
char		*my_strchr(const char *str, int c);
int			count(char **str);
int			is_no(char *str);
void		ft_echo(char **str);
char		**ft_split_with_slash(char *str, char cut);
void		ft_pwd();
int			equal(char *str);
void		fill_env(char **env);
void		ft_env();
int			ft_count(char **str);
void		chnage_old_pwd(char *cmd);
void		ft_cd(char **cmd);
void		print_export();
char		*the_name(char *str);
int			check_if(t_file *str, char type);
int			my_lstsize(t_execute *lst);
void		error_print(int i, char *cmd);
void		my_close(t_va *va);
void		ft_close(t_va *va, t_exeuction *str);
void		handle_here_doc(t_file *str);
void		handle_input(t_file *file);
void		handle_append(t_file *file);
void		handle_output(t_file *file);
void		handle_redir(t_exeuction *str, t_va *va);
void		read_from_here_doc(t_file *file);
void		handle_other_input(t_exeuction *str, t_va *va);
int			check_if_built(t_exeuction *str);
void		init(t_va *va);
char		*the_value(char *str);
int			before_is_plus(char *str);
int			update(char *str);
void		add_to_exp(char *str);
int			myreadline(char **str);
void		ft_free(char **str);
void		add_to_export(char **cmd);
void		chnage_old_pwd(char *cmd);
void		ft_export(char **cmd);
void		ft_unset(char **str);
int			ft_lstsize(t_exeuction *lst);
void		ft_exit(char **str);
void		execution(t_exeuction *str);
char		**get_env(void);
int	ft_isalnum(int a);
void	*ft_calloc(size_t count, size_t size);
int	handle_redir_one_comand(t_exeuction *str);
void	dup_here(t_file *str);
#endif