/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:45:38 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/11 18:06:41 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static int	helper_function(const char *s, int *type)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
			i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			*type = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *s)
{
	int			i;
	long		x;
	int			type;
	int			l;

	type = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		i++;
	}
	i = helper_function(s, &type);
	x = 0;
	l = 0;
	while (s[i] <= '9' && s[i] >= '0')
	{
		x = x * 10 + (s[i] - 48);
		if (l > x)
		{
			if (type < 0)
				return (0);
			else if (type > 0)
				return (-1);
		}
		i++;
		l = x;
	}
	return (x * type);
}

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '+' || str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int check_if_it_isfirst(char *str)
{
	t_execute *ptr;
	char *plr;
	plr = name_without_equal(g_data.str->name);
	if (strcmp(str, plr) == 0)
	{
		ptr = g_data.str;
		g_data.str = g_data.str->next;
		free(ptr->name);
		free(ptr->value);
		free(ptr);
		free(plr);
		return (1);
	}
	free(plr);
	return (0);
}

void	check_if_there_and_unset_it(char *str)
{
	t_execute	*ptr;
	t_execute	*temp;
	t_va		av;
	

	av.i = 0;
	temp = g_data.str;
	if (temp == NULL)
		return ;
	if (check_if_it_isfirst(str) == 1)
		return;
	while (temp)
	{
		if (temp->next == NULL)
			return; 
		av.comd = name_without_equal(temp->next->name);
		if (strcmp(av.comd, str) == 0)
		{
			ptr = temp->next;
			temp->next = temp->next->next;
			free(ptr->name);
			free(ptr->value);
			free(ptr);
			return ;
		}
		temp = temp->next;
	}
}

void	ft_unset(char **str)
{
	t_va	va;

	va.i = 1;
	if (ft_count(str) == 1)
		return;
	while (str[va.i])
	{
		// if (chec__name(str[va.i]) == 1)
		// {
		// 	va.i++;
		// 	continue;
		// }
		check_if_there_and_unset_it(str[va.i++]);

	}

}
void ft_put_error(char *str, char *str1, char *str2)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}

void	handle_many_arguments(char *str)
{
	int	i;

	i  =  ft_atoi(str);
	if (i == -1)
	{
		ft_put_error("exit\nmini: exit: ", str, ": numeric argument requiredn\n");
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit\nmini: exit: too many arguments\n", 2);
		g_data.exit_status = 1;
	}
}
void	handle_one_arguments(char *str)
{
	int	i;

	i  =  ft_atoi(str);
	if (i == -1)
	{
		ft_put_error("exit\nmini: exit: ", str, ": numeric argument required\n");
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit", 1);
		exit(i);
	}
	
}
void help_exit(char **str)
{
	t_va va;

	va.i = 0;
	if (ft_count(str) > 2)
		handle_many_arguments(str[1]);
	else 
		handle_one_arguments(str[1]);
}

void ft_exit(char **str)
{
	if (ft_count(str) != 1)
	{
	
		help_exit(str);
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}
void	ft_echo(char **str)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	if (count(str) > 1)
	{
		while (str[i] && str[i][0] && is_no(str[i]) == 0)
		{
			x++;
			i++;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
		if (x == 0)
			printf("\n");
	}
	g_data.exit_status = 0;
}

void	ft_env()
{
	t_execute	*temp;
	temp = g_data.str;
	while (temp)
	{
		if (my_strchr(temp->name , '=') != NULL)
		{
			ft_putstr_fd(temp->name, 1);
			if (temp->value != NULL)
				ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
	g_data.exit_status = 0;
}
char *name_without_equal(char *str)
{
	int i;
	int x;
	char *ptr;
	i = 0;
	x = 0;
	
	while(str && str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (i == 0)
		return (NULL);
	ptr = calloc((sizeof(char ) * i + 1), 1);
	while (str[x] && x < i)
	{
		ptr[x] = str[x];
		x++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char *ft_getenv(char *cmd)
{
	t_execute *temp;
	char *st;
	temp = g_data.str;
	while(temp)
	{
		st = name_without_equal(temp->name);
		if (strcmp(st, cmd) == 0)
		{
			return (strdup(temp->value));
		}
		free(st);
		temp = temp->next;
	}
	return (NULL);
}
void ft_cd(char **cmd)
{
	int	i;
	char *pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (ft_count(cmd) == 1)
	{
		if (chdir(ft_getenv("HOME")) == -1)
		{
			g_data.exit_status = 1;
			printf("bash: cd: HOME not set\n");
		}
		chnage_old_pwd(pwd);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			printf("bash: cd: %s: No such file or directory", cmd[1]);
			g_data.exit_status = 1;
		}
		chnage_old_pwd(pwd);
	}
}

void ft_export(char **cmd)
{
	if (ft_count(cmd) == 1)
	{
		print_export();
		g_data.exit_status = 0;
	}
	else
		add_to_export(cmd);
}

void ft_pwd()
{
	char	str[PATH_MAX];
	
	getcwd(str, sizeof(str));
	printf("%s\n", str);
	g_data.exit_status = 0;
}

