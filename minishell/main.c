
#include "execution.h"
int main(int ac, char *av[], char *env[])
{
	// char **ptr;
	// char *str;
	// 	int *fds = malloc(sizeof(int) * 2);
	// fds[0] = dup(0);
	// fds[1] = dup(1);

	fill_env(env);
	// while (1)
	// {
	// 	while (myreadline(&str) != 0 )
	// 	{

	// 	}
	// 	ptr  = ft_split(str,  ' ');
	// 	if (ptr == NULL)
	// 		continue;
	// 	if (strcmp(ptr[0], "echo") == 0)
	// 		ft_echo(ptr);
	// 	else if (strcmp(ptr[0], "cd") == 0)
	// 		ft_cd(ptr);
	// 	else if (strcmp(ptr[0], "env") == 0)
	// 		ft_env();
	// 	else if (strcmp(ptr[0], "pwd") == 0)
	// 		ft_pwd();
	// 	else if (strcmp(ptr[0], "export") == 0)
	// 		ft_export(ptr);
	// 	else if (strcmp(ptr[0], "exit") == 0)
	// 		ft_exit(ptr);
	// 	else if (strcmp(ptr[0], "unset") == 0)
	// 		ft_unset(ptr);
	// 	else 
	// 		system(str);
	// 	dup2(0, fds[0]);
	// 	dup2(1, fds[1]);
	// 	ft_free(ptr);
	// 	}



	// fill_env(env);
	// t_exeuction *str = malloc(sizeof(t_exeuction));
	// str->str = "cat";
	// while (1)
	// {
	// 	while (myreadline(&str) != 0 )
	// 	{

	// 	}
	// 	ptr  = ft_split(str,  ' ');
	// 	if (ptr == NULL)
	// 		continue;
	// 	if (strcmp(ptr[0], "echo") == 0)
	// 		ft_echo(ptr);
	// 	else if (strcmp(ptr[0], "cd") == 0)
	// 		ft_cd(ptr);
	// 	else if (strcmp(ptr[0], "env") == 0)
	// 		ft_env();
	// 	else if (strcmp(ptr[0], "pwd") == 0)
	// 		ft_pwd();
	// 	else if (strcmp(ptr[0], "export") == 0)
	// 		ft_export(ptr);
	// 	else 
	// 		system(str);
	// 	dup2(0, fds[0]);
	// 	dup2(1, fds[1]);
	// 	ft_free(ptr);
	// }
// 	fill_env(env);
// 	t_exeuction *str = calloc(sizeof(t_exeuction), 1);
//     str->str = malloc(sizeof(char *) * 1);
// 	str->str[0] = "cat";
//     str->file = NULL;
//    t_exeuction *ptr = calloc(sizeof(t_exeuction), 1);
//     ptr->str = malloc(sizeof(char *) * 1);
// 	ptr->str[0] = "cat";
//     ptr->file = NULL;
//     str->next = ptr;
//     ptr = calloc(sizeof(t_exeuction), 1);
//     ptr->str = malloc(sizeof(char *) * 1);
// 	ptr->str[0] = "ls";
//     ptr->file = NULL;
//     ptr->next = NULL;
//     str->next->next = ptr;
// 	execution(str);
	// str->file = malloc(sizeof(t_file));
	// str->file->name = "main.c";
	// str->file->type = 'I';
	// str->file->next = NULL;
	// t_exeuction *ptr = malloc(sizeof(t_exeuction));
	// ptr->str = "cat";
	// ptr->file = malloc(sizeof(t_file));
	// ptr->file->name = "ma";
	// ptr->file->type = 'O';
	// ptr->file->next = NULL;
	// str->next = ptr; 
	// execution(str);
	// t_exeuction *str = malloc(sizeof(t_exeuction));
	// str->file = malloc(sizeof(t_file));
	// str->file->name = "l";
	// str->file->type = 'O';
	// str->file->next = malloc(sizeof(t_file));
	// str->file->next->name = "outfile1";
	// str->file->next->type = 'O';
	// str->str = malloc(sizeof(char *) * 1);
	// str->str[0] = "ls";
	// t_file *file = malloc(sizeof(t_file));
	// file->name = "main.c";
	// file->type = 'I';
	// file->next = NULL;
	// str->file->next->next = file;
	// str->next = NULL;
	// file = malloc(sizeof(t_file));
	// file->name = "Makefile";
	// file->type = 'I';
	// file->next = NULL;
	// str->file->next->next->next = file;

	execution(str);
}