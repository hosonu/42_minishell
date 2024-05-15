/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoyuki <hoyuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:35 by kojwatan          #+#    #+#             */
/*   Updated: 2024/05/15 18:55:29 by hoyuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

typedef struct s_token
{
	char			*token;
	int8_t			type;
	uint8_t			pipein;
	uint8_t			pipeout;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_quotes
{
	char			*open;
	char			*close;
}					t_quotes;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_fdgs
{
	int				pp[2];
	int				gfd[2];
	int				original_stdin;
	int				original_stdout;
}					t_fdgs;

typedef struct s_status
{
	int				exit_status;
	int				exit_code;
	int				is_file;
	int				cnt_file;
}					t_status;

typedef struct s_ige
{
	int				waiting_for_sige;
}					t_ige;

# define METAOUT -1
# define METAAPNDOUT -1
# define METAIN -2
# define METAHEREDOC -4
# define METAPIPE -8

# define TRUNCOUTFILE 10
# define APNDOUTFILE 15
# define INFILE 20
# define HEREDOC 25

# define COMMAND 30
# define REOUTCOMMAND 31
# define REINCOMMAND 32
# define REINOUTCOMMAND 33
# define HEREDOCCOMMAND 34
# define REOUTHEREDOCCOMMAND 35

#endif
