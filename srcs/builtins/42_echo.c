/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:38:21 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/24 01:23:15 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	get_option_n(char *argv)
{
	size_t	i;

	i = 0;
	if (argv[0] == '-' && argv[1] == 'n')
	{
		while (argv[i + 1] != '\0' && argv[i + 1] == 'n')
			i++;
		if (ft_strlen(argv) - 1 == i)
			return (true);
	}
	return (false);
}

int	cnt_option_n(char **argv)
{
	int	i;

	i = 0;
	while (argv[i + 1] != NULL)
	{
		if (get_option_n(argv[i + 1]) == false)
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char *argv[])
{
	bool	is_noline;
	int		cnt_opt;

	is_noline = false;
	cnt_opt = 0;
	if (argv[1] == NULL)
		write(1, "\n", 1);
	else
	{
		is_noline = get_option_n(argv[1]);
		if (is_noline == true)
			cnt_opt = cnt_option_n(argv);
		while (argv[1 + cnt_opt] != NULL)
		{
			write(1, argv[1 + cnt_opt], ft_strlen(argv[1 + cnt_opt]));
			if (argv[1 + cnt_opt + 1] != NULL)
				write(1, " ", 1);
			cnt_opt++;
		}
		if (is_noline == false)
			write(1, "\n", 1);
	}
	return (0);
}
