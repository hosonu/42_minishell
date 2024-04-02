/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:00:08 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 16:15:02 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_chain_tokens(t_token *top)
{
	while(top != NULL)
	{
		ft_printf("DEBUG before sort: token [%s]\ttype %d\n", top->token, top->type);
		top = top->next;
	}
}

void	print_linear_tokens(t_token **top)
{
	int	i;

	i = 0;
	while (top[i])
	{
		printf("DEBUG after sorted: token [%s]\ttype %d\n", top[i]->token, top[i]->type);
		i++;
	}
}

void	print_quote(t_quotes *list)
{
	int	i;

	i = 0;
	while (list[i].open != NULL)
	{
		//printf("DEBUG printf_quote: LEFT %p RIGHT %p\n", list[i].left, list[i].right);
		i++;
	}
}
