  #include "include/minishell.h"

void print_str_array(char **arr) {
    for (int i = 0; arr[i] != NULL; i++) {
        printf(" str = %s\n", arr[i]);
    }
}


 int main(int ac, char *av[], char *env[])
 {
	t_exeuction *ptr;
	char *str;
	ac = 0;
	av = env;
	fill_env(env);
	int fd[2];
	fd[0] = dup(0);
	fd[1] = dup(1);
	while(1)//while 1 atb9a testi testi ta t3ia
	{
		str = readline("mini-3.2$ : ");//this function is like get_next_line kat9ra mn stdin 
		if (str == NULL)
		{
			ft_putstr_fd("exit", 1);
			return (0);
		}
		 ptr  = filed_struct(str);
		// if (ptr->file == NULL)
		 execution(ptr);
		 add_history(str);
		 dup2(fd[0], 0);
		 dup2(fd[1], 1);
		// t_token *token;
		// t_file *file;
		// token = NULL;
		// token = lexer(str);
		// t_exeuction *exec;
		// exec = NULL;
		// exec = filed_struct(str);
		
		// // exec = exec->next;
		// // printf("fgdh\n");
		// // print_str_array(exec->str);
		
		// file = exec->file;
		// // while (token)
		// // {
		// // 	printf("token->value %s\n", token->value);
		// // 	printf("token->type %u\n", token->type);
		// // 	token = token->next;
		// // }

		// int j = 0;
		// while (exec)
		// {
		// 	print_str_array(exec->str);
		// 	printf(" j = %d\n",j);
		// 	exec = exec->next;
		// }
	}
 }