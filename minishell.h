/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:31:28 by kojwatan          #+#    #+#             */
/*   Updated: 2024/03/21 14:54:47 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define METAOUT -1
# define METAAPNDOUT -2
# define METAIN -3
# define METAHEREDOC -4
# define METAPIPE -5
# define OWOUTFILE 10
# define APNDOUTFILE 11
# define INFILE 20
# define HEREDOC 21
# define COMMAND 30
//# define REINCOMMAND 31
//# define REOUTCOMMAND 32
//# define REINTOUTCOMMAND 33
# define PIPEOUTCOMMAND 34
# define PIPEINCOMMAND 35
# define PIPEINOUTCOMMAND 36

typedef struct s_token
{
	char			*token;
	int	type;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

int		token_len(char *src);
int	is_metachar(char c);
char	*tokenizer(char *str);
char	*make_right(char *str);
void	decide_type_util(t_token *token, int meta_type, int type);
int	decide_type(t_token *top);
char	*strdup_right(char *str);
t_token	*new_token(char *content);
t_token	*lexer(char *str);
void	token_addlast(t_token *top, t_token *new);
void	check(t_token *top);
t_token	*devide_file(t_token *node);
t_token	*devide_cmd(t_token *node);
void	token_insert(t_token *node, t_token *new);
void	token_destroy(t_token *node);
t_token	**linear_token_list(t_token *top);
void	sort_token(t_token **list);
void	print_to(t_token **top);

#endif
