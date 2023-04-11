/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 23:31:29 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/11 17:57:08 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	myreadline(char **str)
{
	*str = readline("mini-3.2$ ");
	if (strcmp(*str, "") == 0)
		return (1);
	if (strlen(*str) > 0)
		add_history(*str);
	return (0);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_help_chnage_pld_pwd(char *cmd, int *i, int *x)
{
	t_execute	*g;

	g = g_data.str;
	while (g)
	{
		if (strcmp("OLDPWD=", g->name) == 0)
		{
			*i = 1;
			free(g->value);
			g->value = cmd;
		}
		if (strcmp("PWD=", g->name) == 0)
		{
			*x = 1;
			free(g->value);
			g->value = getcwd(NULL, 0);
		}
		g = g->next;
	}
}

void	chnage_old_pwd(char *cmd)
{
	int			i;
	int			x;

	i = 0;
	x = 0;
	ft_help_chnage_pld_pwd(cmd, &i, &x);
	if (i == 0)
		my_lstadd_back(&g_data.str, \
			my_lstnew(my_strdup("OLDPWD="), cmd));
	if (i == 0)
		my_lstadd_back(&g_data.str, \
			my_lstnew(my_strdup("PWD="), getcwd(NULL, 0)));
}
