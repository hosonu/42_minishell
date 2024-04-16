/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:31:28 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/16 15:24:09 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "./define.h"
# include "./lexer.h"
# include "./tokenize.h"
# include "./token_type.h"
# include "./sort_token.h"
# include "./prompt_validate.h"
# include "./debug.h"
# include "./free.h"
# include "./string_utils.h"
# include "env.h"
# include "./ft_builtins.h"
# include "./token_split.h"
# include "token_runner.h"
# include "x_func.h"
# include "error_msg.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

#endif
