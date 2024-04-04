/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_validate.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:59 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/04 00:18:19 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_VALIDATE_H
# define PROMPT_VALIDATE_H

#include "./minishell.h"

int	prompt_validate(char *prompt);
int	redirect_validate(char *str);
int	quotation_validate(char *str);

#endif
