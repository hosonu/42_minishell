/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:59:16 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/03 02:06:40 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include "./minishell.h"

t_token	*devide_file(t_token *node);
t_token	*devide_cmd(t_token *node);
void	token_revise(t_token *top);
void	token_type_revise(t_token **list);
int	decide_type_util(t_token *token, int8_t meta_type, int8_t type);
int	decide_type(t_token *top);

#endif
