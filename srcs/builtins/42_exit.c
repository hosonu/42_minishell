/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:49 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/25 15:14:19 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_sign_and_space(char *str, int *sign)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign *= -1;
		str++;
	}
}

int	ft_atoll_safe(char *str)
{
	long long	result;
	int			sign;
	int			digit;

	result = 0;
	sign = 1;
	skip_sign_and_space(str, &sign);
	while (*str != '\0')
	{
		digit = *str - '0';
		if (sign == 1 && (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
					&& digit > LLONG_MAX % 10)))
			return (1);
		else if (sign == -1 && (-result < LLONG_MIN / 10
				|| (-result == LLONG_MIN / 10 && digit * -1 < LLONG_MIN % 10)))
			return (1);
		result = result * 10 + digit;
		str++;
	}
	return (0);
}

int	check_digits(char *str)
{
	size_t	i;
	int		is_sign;

	i = 0;
	is_sign = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if ((ft_isdigit(str[i]) != 1 && str[i] != '+' && str[i] != '-'))
		return (0);
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		is_sign = 1;
		i++;
	}
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '\0' && i == 1 && is_sign == 1)
		return (0);
	else if (str[i] == '\0')
		return (1);
	else
		return (2);
}

void	ft_exit(char *av[], int status, bool is_parent, t_env *env)
{
	if (is_parent == true)
		write(2, "exit\n", 5);
	if (av[1] != NULL && check_digits(av[1]) == 1)
	{
		if (ft_atoll_safe(av[1]) == 1)
		{
			err_msg_for_exit(av[1]);
			status = 255;
		}
		else if (av[2] != NULL)
		{
			write(2, "minish: exit: too many arguments\n", 33);
			return ;
		}
		status = ft_atoi(av[1]);
	}
	else if (av[1] != NULL && check_digits(av[1]) != 1)
	{
		err_msg_for_exit(av[1]);
		status = 255;
	}
	free_env(env);
	exit(status);
}
