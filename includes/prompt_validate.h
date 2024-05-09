/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/25 15:24:19 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_VALIDATE_H
# define PROMPT_VALIDATE_H

# include "./minishell.h"

int	prompt_validate(char *prompt);
int	syntax_validate(t_token *tokens, t_status *status);
int	quotation_validate(char *str, t_status *status);
int	metachar_validate(t_token *node, t_status *status);

#endif
