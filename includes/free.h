/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:57:45 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:57:45 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "./minishell.h"

void	free_linear_token_list(t_token **list);
void	free_chain_token_list(t_token *top);
void	free_env(t_env *env);

#endif
