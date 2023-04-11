/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:04:45 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/04/03 18:50:43 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// initializ the redirection 
t_file *initialize_redirection(char *filename, char type)
{
	t_file *red;
	
	if (!filename)
		return (NULL);
	red = (t_file *)malloc(sizeof(t_file));
	if (!red)
		return (NULL);
	red->name = filename;
	red->type = type;
	red->next = NULL;
	return (red);
}
//initializ the execution struct
t_exeuction *initialize_execution(char **str, t_file *file)
{
	t_exeuction *cmd;
	
	if (!str)
		return (NULL);
	cmd = (t_exeuction *)malloc(sizeof(t_exeuction));
	if (!cmd)
		return (NULL);
	cmd->str = str;
	cmd->file = file;
	cmd->next = NULL;
	return (cmd);
}

t_exeuction *last_exec(t_exeuction *exec)
{
	if (!exec)
		return (NULL);
	while (exec->next != NULL)
		exec = exec->next;
	return (exec);
}
// remplie liste d'execution
void add_back_execution(t_exeuction **list_exec, t_exeuction *exec)
{
	t_exeuction *tmp;

	tmp = (*list_exec);
	if (!(*list_exec))
		(*list_exec) = exec;
	else 
	{
		tmp = last_exec(*list_exec);
		tmp->next = exec;
	}
}

t_file *last_file(t_file *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void add_back_file(t_file **list_file, t_file *file)
{
	t_file *tmp;
	
	tmp = (*list_file);
	if (!(*list_file))
		(*list_file) = file;
	else
	{
		tmp = last_file((*list_file));
		tmp->next = file;
	}
}