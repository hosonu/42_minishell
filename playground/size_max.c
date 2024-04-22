#include <limits.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


static long long	ft_validate_long(const char *str, long long sign)
{
	long long	nb;

	nb = 0;
	while (*str && (ft_isdigit(*str)))
	{
		if ((nb * sign) > (LLONG_MAX - (*str - '0')) / 10)
			return (LLONG_MAX);
		if ((nb * sign) < (LLONG_MIN + (*str - '0')) / 10)
			return (LLONG_MIN);
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

long long	ft_atoi(const char *str)
{
	long long	sign;

	sign = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return ((ft_validate_long(str, sign)));
}

#include <stdio.h>
int main()
{
	long long num = ft_atoi("9223372036854775807");
	printf("%lld\n", num);
	return 0;
}

