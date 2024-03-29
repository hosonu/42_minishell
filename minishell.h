/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:31:28 by kojwatan          #+#    #+#             */
/*   Updated: 2024/03/29 09:12:33 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define METAOUT -1
# define METAAPNDOUT -1
# define METAIN -4
# define METAHEREDOC -8
# define METAPIPE -16
# define OWOUTFILE 10
# define APNDOUTFILE 11
# define INFILE 20
# define INFILETOPIPE 22
# define HEREDOC 23
# define COMMAND 30
# define REINCOMMAND 34
# define REINPIPEOUTCOMMAND 36
# define REOUTCOMMAND 31
# define REINOUTCOMMAND 35
# define REINOUTPIPEOUTCOMMAND 40
# define PIPEINCOMMAND 46
# define REOUTPIPEINCOMMAND 47
# define REOUTPIPEINOUTCOMMAND 48
# define REINPIPEINCOMMAND 50
# define REINOUTPIPEINCOMMAND 51
# define REINOUTPIPEINOUTCOMMAND 52
# define PIPEOUTCOMMAND 60
# define PIPEINOUTCOMMAND 53
# define HEREDOCCOMMAND 38
# define REOUTHEREDOCCOMMAND 39
# define REINHEREDOCCOMMAND 42
# define REINOUTHEREDOCCOMMAND 43
# define REOUTPIPEOUTHEREDOCCOMMAND 56
# define PIPEINHEREDOCCOMMAND 54
# define PIPEOUTHEREDOCCOMMAND 55
# define PIPEINOUTHEREDOCCOMMAND 57
# define REINOUTPIPEINHEREDOCCOMMAND 59
# define REINOUTPIPEINOUTHEREDOCCOMMAND 58


typedef struct s_token
{
	char			*token;
	int	type;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

typedef struct s_quotes
{
	char	*open;
	char	*close;
}	t_quotes;

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
void	token_revise(t_token *top);
t_token	*devide_file(t_token *node);
t_token	*devide_cmd(t_token *node);
void	token_insert(t_token *node, t_token *new);
void	token_destroy(t_token *node);
t_token	**linear_token_list(t_token *top);
void	sort_token(t_token **list);
void	print_to(t_token **top);
void	quotation_validate(char *str);
int	count_chr(char *str, char c);
t_quotes	*quote_list(char *str, char quote);
void	print_quote(t_quotes *list);
void	metachr_quote_revise(char *str, char *pnt[5]);
void	validate_quote_nesting_util(t_quotes *list, t_quotes quotes);
void	validate_quote_nesting(t_quotes *list1, t_quotes *list2);
void	token_type_revise(t_token **list);

#endif
