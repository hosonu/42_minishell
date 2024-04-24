/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-23 16:45:48 by user              #+#    #+#             */
/*   Updated: 2024/04/24 21:15:01 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_HANDLE_H
# define PROMPT_HANDLE_H

# include "./minishell.h"

t_token	**prompt_handle(t_env *env, t_status *status);
t_token	**token_list(t_token *tokens, t_status *status);

#endif
