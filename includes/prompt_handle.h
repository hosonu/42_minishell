/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:45:48 by user              #+#    #+#             */
/*   Updated: 2024-04-23 16:45:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_HANDLE_H
# define PROMPT_HANDLE_H

# include "./minishell.h"

t_token	**prompt_handle(void);
t_token	**token_list(t_token *tokens);

#endif
