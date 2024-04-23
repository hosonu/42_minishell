/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/19 01:20:08 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_VALIDATE_H
# define PROMPT_VALIDATE_H

# include "./minishell.h"

int	prompt_validate(char *prompt);
int	syntax_validate(t_token *tokens);
int	quotation_validate(char *str);
int	metachar_validate(t_token *node);

#endif
