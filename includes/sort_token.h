/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_token.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:59:08 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 01:48:02 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_TOKEN_H
# define SORT_TOKEN_H

# include "./minishell.h"

void	print_to(t_token **top);
t_token	**linear_token_list(t_token *top);
void	v_sort_token(t_token **top);
void	sort_token(t_token **list);

#endif
