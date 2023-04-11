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
		 add_history(str);
		if (str == NULL)
		{
			ft_putstr_fd("exit", 1);
			return (0);
		}
		 ptr  = filed_struct(str);
		if (ptr == NULL)
			continue;
		 execution(ptr);
		 dup2(fd[0], 0);
		 dup2(fd[1], 1);
		 free(str);
	}
 }