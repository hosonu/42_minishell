/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:31:28 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/25 15:07:02 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "./define.h"
# include "./tokenize.h"
# include "./token_type.h"
# include "./sort_token.h"
# include "./prompt_validate.h"
# include "./token_join.h"
# include "./debug.h"
# include "./free.h"
# include "./string_utils.h"
# include "env.h"
# include "./heredoc_init.h"
# include "./ft_builtins.h"
# include "./token_split.h"
# include "./my_split.h"
# include "./prompt_handle.h"
# include "token_runner.h"
# include "x_func.h"
# include "error_msg.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

#endif
