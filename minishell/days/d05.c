/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d05.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:27:06 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/06 00:47:01 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


int	handle_input_for_one_comand(t_file *file)
{
	int	fds;

	fds = open(file->name, O_RDWR, 0644);
	if (fds == -1)
	{
		perror("open");
        g_data.exit_status = 1;
		return (1);
	}
	dup2(fds, 0);
	close(fds);
    return (0);
}

int	handle_append_for_one_comand(t_file *file)
{
	int	fds;

	fds = open(file->name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fds == -1)
	{
        g_data.exit_status = 1;
		perror("open");
		return (1);
	}
	dup2(fds, 1);
	close(fds);
    return (0);
}

int	handle_output_for_one_comand(t_file *file)
{
	int	fds;

	fds = open(file->name, O_CREAT | O_RDWR, 0644);
	if (fds == -1)
	{
        g_data.exit_status = 1;
		perror("open");
		return (1);
	}
	dup2(fds, 1);
	close(fds);
    return (0);
}

int	handle_redir_one_comand(t_exeuction *str)
{
	t_file	*file;

	file = str->file;
	while (file)
	{
		if (file->name)
		{
			if (file->type == 'H')
				dup_here(file);
			else if (file->type == 'I')
				return (handle_input_for_one_comand(file));
			else if (file->type == 'A')
				return (handle_append_for_one_comand(file));
			else if (file->type == 'O')
				return (handle_output_for_one_comand(file));
		}
		file = file->next;
	}
    return (0);
}