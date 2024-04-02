/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kojwatan <kojwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 22:58:35 by kojwatan          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:24 by kojwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

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
# define REINPIPEINOUTCOMMAND 49
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

# endif
