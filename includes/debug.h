/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosonu <hoyuki@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 01:39:21 by hosonu            #+#    #+#             */
/*   Updated: 2024/04/24 01:39:31 by hosonu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "./minishell.h"

void	print_linear_tokens(t_token **top);
void	print_chain_tokens(t_token *top);
void	print_quote(t_quotes *list);

#endif
