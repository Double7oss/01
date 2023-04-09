/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:33:06 by abouzanb          #+#    #+#             */
/*   Updated: 2023/04/05 16:12:12 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}



// char every_no_terry(char *str)
// {
	
// }
// int add_to_unvalue(char *str)
// {
// 	t_va va;
// 	va.comd = the_name(str);
// 	if (stch)                                  
// }




int	equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

