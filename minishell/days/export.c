#include "../execution.h"

void	print_export(void)
{
	t_execute	*ptr;

	ptr = g_data.str;
	while (ptr)
	{
		printf("declare -x %s", ptr->name);
		if (ptr->value)
			printf("\"%s\"", ptr->value);
		printf("\n");
		ptr = ptr->next;
	}
}
int	is_valid(char *str)
{
	int	i;
	int	j;

	i = 0;

		j = 0;
		if (str[0] == '\0')
		{
			ft_putstr_fd("bash: export: `': not a valid identifier\n", 2);
			g_data.exit_status = 1;
			return (0);
		}
		if (ft_isdigit(str[0]) == 1 || str[0] == '=')
		{
            ft_putstr_fd("bash: export: `",2 );
            ft_putstr_fd(str, 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
			g_data.exit_status = 1;
			return (0);
		}
		while (str && str[i])
		{
			if (str[i] == '=')
				return (1);
			if (str[i] == '+')
			{
				if (str[i + 1]!= '=')
				{
                    ft_putstr_fd("bash: export: `",2 );
                    ft_putstr_fd(str, 2);
                    ft_putstr_fd("': not a valid identifier\n", 2);
					g_data.exit_status = 1;
					return (1);
				}
			}
			if (ft_isalnum(str[i]) == 0 && str[i] != '+')
            {
                ft_putstr_fd("bash: export: `",2 );
                ft_putstr_fd(str, 2);
                ft_putstr_fd("': not a valid identifier\n", 2);
				return (0);
            }
            i++;
		}
	return (1);
}
int already_is(char *str)
{
	t_execute *s;
	char	*ss;
	char *test;
	char *no_e;

	s = g_data.str;
	while (s)
	{
		no_e = name_without_equal(str);
		ss = the_name(str);
		test = name_without_equal(s->name);
		if (strcmp(s->name, ss) == 0)
		{
			free(ss);
			free(s->value);
			free(test);
			s->value = the_value(str);
			return (0);
		}
		if (strcmp(s->name ,no_e) == 0)
		{
			free(test);
			free(no_e);
			free(s->name);
			free(s->value);
			s->value = the_value(str);
			s->name = the_name(str);
			return (0);
		}
		else if (strcmp(test, str) == 0)
		{
			free(test);
			return (0);
		}
		free(test); 
		free(no_e);
		free(ss);
		s = s->next;
	}
	return (1);
}
void add_to_exp(char *str)
{
	char	*name;
	char	*value;

		
	if (update(str) == 0)
		return ;
	if (already_is(str) == 0)
		return ;
	name = the_name(str);
	value = the_value(str);
	my_lstadd_back(&g_data.str, my_lstnew(name, value));
}

void add_to_export(char **cmd)
{
	int i;
	i = 1;

	while (cmd[i])
	{	
		if (is_valid(cmd[i]) != 0)
            add_to_exp(cmd[i]);
		i++;
	}
}




int update(char *str)
{
	t_execute *s;
	char *ptr;
	char *temp;

	s = g_data.str;
	if (before_is_plus(str) != 0)
	{
		while (s)
		{
			ptr =  the_name(str);
			if (strcmp(s->name, ptr) == 0)
			{
				free(ptr);
				temp = s->value;
				ptr = the_value(str);
				s->value = my_strjoin(s->value, ptr);
				free(temp);
				free(ptr);
				return (0);
			}
			free(ptr);
			s = s->next;
		}
	}
	return (1);
}



int	is_no(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0' || str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}



int cont_size_off_the_name(char *str)
{
	int i;
	int x;

	i =0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+')
			i++;
		else
		{
			x++;
			i++;
		}
	}
	return x;

}
char	*the_name(char *str)
{
	int		i;
	int		x;
	char	*ptr;

	i = 0;
	x = cont_size_off_the_name(str);
	ptr = malloc((sizeof(char ) * x + 3));
	x = 0;
	i = 0;
	while (str[i])
	{
		ptr[x] = str[i];
		x++;
		i++;
		if (str[i] == '+')
			i++;
		if (str[i] == '=')
		{
			ptr[x] = str[i];
			x++;
			break ;
		}
	}
	ptr[x] = '\0';
	return (ptr);
}

char *the_value(char *str)
{
	char *ptr;
	int i;
	int a;
	int x;

	x = 0;
	i = 0;

	while (str[i] && str[i] != '=')
		i++;
	
	if (str[i] == '\0')
		return (NULL);
	a = i;
	while (str[a])
		a++;
	ptr = malloc((sizeof(char ) * a + 1));
	if (ptr == NULL)
		return (NULL);
	i++;
	while (str[i])
	{
		ptr[x] = str[i];
		x++;
		i++;
	}
	ptr[x] = '\0';
	return (ptr);
}

int before_is_plus(char *str)
{
	int	i;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
		{
			if (i != 0 && str[i - 1] == '+')
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
