/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d02.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:35:11 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/04 02:24:32 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	handle_here_doc(t_file *str)
{
	int		fd[2];
	int		x;
	char	*ptr;

	pipe(fd);
	x = fork();
	if (x == 0)
	{
		while (1)
		{
			ptr = readline("> ");
			if (ptr == NULL)
			{
				close(fd[1]);
				close(fd[0]);
				exit (0);
			}
			if (strcmp(str->name, ptr) == 0)
			{
				close(fd[1]);
				close(fd[0]);
				exit(0);
			}
			write(fd[1], ptr, my_strlen(ptr));
			write(fd[1], "\n", 1);
		}
	}
	str->here_doc = dup(fd[0]);
	close(fd[1]);
	close(fd[0]);
	waitpid(x, 0, 0);
}

void	handle_input(t_file *file)
{
	int	fds;

	fds = open(file->name, O_RDWR, 0644);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 0);
	close(fds);
}

void	handle_append(t_file *file)
{
	int	fds;

	fds = open(file->name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}

void	handle_output(t_file *file)
{
	int	fds;

	fds = open(file->name, O_CREAT | O_RDWR, 0644);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}
