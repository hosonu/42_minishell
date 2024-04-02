/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotation_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:00:23 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 15:47:00 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotation_validate(char *str)
{
	int	single_quote_count;
	int	double_quote_count;
	t_quotes	*single_list;
	t_quotes	*double_list;

	//printf("DEBUG quotation_validate: str %s\n", str);
	single_quote_count = count_chr(str, '\'');
	double_quote_count = count_chr(str, '\"');
	if (single_quote_count % 2 == 1 || double_quote_count % 2 == 1)
	{
		perror("Quotation Error");
		return (-1);
	}
	single_list = quote_list(str, '\'');
	double_list = quote_list(str, '\"');
	if (validate_quote_nesting(single_list, double_list) < 0)
		return (-1);
	free(single_list);
	free(double_list);
	return (1);
}

int	validate_quote_nesting_util(t_quotes *list, t_quotes quotes)
{
	int i;

	i = 0;
	while (list[i].open != NULL)
	{
		if (list[i].open < quotes.open && quotes.close < list[i].close)
			return (1);
		else if (!(list[i].open < quotes.open) && !(quotes.close < list[i].close))
			;
		else if (list[i].close < quotes.open)
			;
		else if (quotes.close < list[i].open)
			;
		else
		{
			perror("Quotation Nesting Error");
			return (-1);
		}
		i++;
	}
	return (1);
}

int	validate_quote_nesting(t_quotes *list1, t_quotes *list2)
{
	int	i;

	if (list1 == NULL || list2 == NULL)
		return (1);
	//printf("DEBUG validate_quote_nesting: \n");
	i = 0;
	while (list1[i].open != NULL)
	{
		if (validate_quote_nesting_util(list2, list1[i]) < 0)
			return (-1);
		i++;
	}
	i = 0;
	while (list2[i].open != NULL)
	{
		if (validate_quote_nesting_util(list1, list2[i]) < 0)
			return (-1);
		i++;
	}
	return (1);
}


int	count_chr(char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_quotes	*quote_list(char *str, char quote)
{
	int	i;
	int	count;
	t_quotes *list;

	i = 0;
	count = count_chr(str, quote);
	if (count == 0)
		return (NULL);
	list = calloc(count + 1, sizeof(t_quotes));
	while (i < count / 2)
	{
		if (i == 0)
			list[i].open = strchr(str, quote);
		else
			list[i].open = strchr(list[i - 1].close + 1, quote);
		list[i].close = strchr(list[i].open + 1, quote);
		i++;
	}
	return (list);
}
