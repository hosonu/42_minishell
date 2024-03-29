/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:48 by kojwatan          #+#    #+#             */
/*   Updated: 2024/03/29 22:58:53 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "./minishell.h"

t_token	*new_token(char *content);
t_token	*lexer(char *str);
void	token_addlast(t_token *top, t_token *new);
void	token_insert(t_token *node, t_token *new);
void	token_destroy(t_token *node);

#endif
