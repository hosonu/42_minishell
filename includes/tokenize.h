/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:59:25 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 00:18:35 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "./minishell.h"

int		token_len(char *src);
void	metachr_quote_revise(char *str, char *pnt[5]);
char	*tokenizer(char *str);
char	*strdup_right(char *str);

#endif
