/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:54:49 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/23 16:57:02 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	err_msg_for_exit(char *str)
{
	write(2, "bash: exit: ", 12);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

int	ft_atoll_safe(const char *str)
{
	long long	result;
	int			sign;
	int			digit;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str != '\0')
	{
		digit = *str - '0';
		if (sign == 1 && (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
					&& digit > LLONG_MAX % 10)))
			return (1);
		else if (sign == -1 && (-result < LLONG_MIN / 10
				|| (-result == LLONG_MIN / 10 && -digit < LLONG_MIN % 10)))
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

void	ft_exit(char *av[], int status)
{
	int	exit_status;

	write(1, "exit\n", 5);
	if (av[1] != NULL && check_digits(av[1]) == 1)
	{
		if (ft_atoll_safe(av[1]) == 1)
		{
			err_msg_for_exit(av[1]);
			exit_status = 255;
		}
		else if (av[2] != NULL)
		{
			write(2, "bash: exit: too many arguments\n", 31);
			return ;
		}
		exit_status = ft_atoi(av[1]);
	}
	else if (av[1] != NULL && check_digits(av[1]) != 1)
	{
		err_msg_for_exit(av[1]);
		exit_status = 255;
	}
	else
		exit_status = status;
	exit(exit_status);
}
