/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:59:16 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/16 16:12:53 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include "./minishell.h"

t_token	*devide_file(t_token *node);
t_token	*devide_cmd(t_token *node);
void	token_revise(t_token *top);
void	token_type_revise(t_token **list);
void	decide_type_util(t_token *token, int8_t meta_type, int8_t type);
void	decide_type(t_token *top);
t_token	**token_list(t_token *tokens);

#endif
