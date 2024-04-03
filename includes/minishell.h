/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:31:28 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 17:48:46 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./define.h"
# include "./lexer.h"
# include "./tokenize.h"
# include "./token_type.h"
# include "./sort_token.h"
# include "./quotation_validate.h"
# include "./debug.h"
# include "./free.h"
// # include "dispatch_token.h"
// # include "manage_fd.h"
// # include "execve_token.h"
// # include "fctl_token.h"

# include "token_runner.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
#endif
