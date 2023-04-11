/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:20:21 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/10 22:34:06 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void free_node(t_exeuction *str)
{
	t_file *file;
	t_file *temp2;
	
	while (str)
	{
		file = str->file;
		while (file)
		{
			free(file->name);
			temp2 = file;
			file = file->next;
			temp2->next = NULL;
			free(temp2);
		}
		ft_free(str->str);
	str = str->next;
	}
}

void check_the_path(t_exeuction *str, t_va *av, char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		av->comd = my_strjoin(path[i], str->str[0]);
		if (access(av->comd, X_OK) == 0)
			return ;
		i++;
	}
	av->comd = NULL;
}
void get_path(t_exeuction *str, t_va *av)
{
	t_execute	*tmp;
	char		**path;


	if ((access(str->str[0], X_OK) == 0))
	{
		av->comd = str->str[0];
		return ;
	}
	if (strchr(str->str[0], '/'))
	{
		av->comd = NULL;
		return;
	}
	tmp = g_data.str;
	if (tmp == NULL)
	{
		av->comd = NULL;
		return ;
	}
	path = NULL;
	while (tmp)
	{
		if (tmp->name && strcmp(tmp->name, "PATH=") == 0)
			path = ft_split_with_slash(tmp->value, ':');
		tmp = tmp->next;
	}
	if (path == NULL)
	{
		av->comd = NULL;
		return ;
	}
	check_the_path(str, av, path);
}

void execute_child(t_exeuction *str, t_va *va)
{
	handle_redir(str, va);
	if (check_if_built(str) == 0)
	{
		get_path(str, va);
		if (va->comd == NULL)
			error_print(1, str->str[0]);
		va->env = get_env();
		my_close(va);
		execve(va->comd, str->str, va->env);
		perror("execve");
		exit(1);
	}
	exit(0);
}

void open_all(t_exeuction *str)
{
	t_file *file;

	while (str)
	{
		file = str->file;
		while (file)
		{
			if (file->type == 'H')
				handle_here_doc(file);
			file  = file->next;
		}
		str = str->next;
	}
}
void creates_childs(t_exeuction *str, t_va *va)
{
	va->k = 0;
	va->i = 0;
	open_all(str);
	while (str)
	{
		va->id = fork();
		if (va->id == -1)
		{
			ft_putstr_fd("mini-3.2$: fork: Resource temporarily unavailable\n", 2);
			g_data.exit_status = 0;
			return;
		}
		if (va->id == 0)
		{
			
			execute_child(str, va);
		}
		ft_close(va, str);
		str = str->next;
		(va->k)++;
	}
}

void	simple(t_exeuction *str, t_va *av)
{
	if (handle_redir_one_comand(str) == 1)
		return ;
	if (check_if_built(str) == 0)
	{

		av->id = fork();
		if (av->id == 0)
		{		
		if (str->str[0][0] == '\0')
		{
			ft_putstr_fd("mini:  : command not found\n", 2);
			exit(127);
		}
			get_path(str, av);
			if (av->comd == NULL)
				error_print(1, str->str[0]);
			av->env = get_env();
			execve(av->comd, str->str, av->env);
			perror("execve");
			exit(1);
		}
		waitpid(av->id, &av->i,0 );
		g_data.exit_status = WEXITSTATUS(av->i);
		free_node(str);
	}
}

void wait_for_them(t_va *va)
{
	int i;
	int status;
	
	i = 0;
	while (i < va->size)
	{
		if (waitpid(-1, &status, 0) == va->id)
			g_data.exit_status = WEXITSTATUS(status);
		i++;
	}
}
void execution(t_exeuction *str)
{

	t_va *va = malloc(sizeof(t_va));	
	va->size = ft_lstsize(str);
	if (va->size == 0)
		return ;
	if (va->size == 1)
	{
		open_all(str);
		simple(str, va);
	}
	else
	{
		va->fd = malloc(sizeof(int *) * va->size - 1);
		init(va);
		if (va->k == -1)
			return;
		creates_childs(str, va);
		wait_for_them(va);
		my_close(va);
		free_node(str);
	}
}
