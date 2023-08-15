/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:20:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 16:23:28 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Classify what type of redirect has been input
*/
static enum e_redirect	flag_redi(char *str)
{
	if (!ft_strncmp(str, "<", 1) && ft_strlen(str) == 1)
		return (INPUT);
	if (!ft_strncmp(str, ">", 1) && ft_strlen(str) == 1)
		return (OUTPUT);
	if (!ft_strncmp(str, "<<", 2) && ft_strlen(str) == 2)
		return (HEREDOC);
	if (!ft_strncmp(str, ">>", 2) && ft_strlen(str) == 2)
		return (APPEND);
	else
		return (BAD_INPUT);
}

static int	check_redirect_type(t_redi *redis)
{
	if (redis->type == 0
		|| redis->type == 2)
	{
		if (open(redis->content, O_RDONLY) < 0)
		{
			g_shell->exit_stat = 1;
			perror("MiniShell");
			return (1);
		}
	}
	if ((redis->type == 1 || redis->type == 3)
		&& (!access(redis->content, F_OK)
			&& open(redis->content, O_WRONLY) < 0))
	{
		ft_putstr_fd("\033[0;31mPermission denied\033[0m\n", 2);
		return (1);
	}
	return (0);
}

int	check_redis(t_list *com)
{
	t_list	*commands;
	t_redi	*redis;

	commands = com;
	while (commands)
	{
		redis = ((t_command *)commands->content)->redi;
		while ((t_command *)redis)
		{
			if (check_redirect_type(redis))
				return (0);
		redis = redis->next;
		}
	commands = commands->next;
	}
	return (1);
}

int	handle_redirects(char *str, t_redi **redi, t_tokens **tokens)
{
	enum e_redirect	flag;
	int				heredoc_flag;

	heredoc_flag = 0;
	flag = NO;
	flag = flag_redi(str);
	if ((*tokens)->next != NULL)
	{
		str = (*tokens)->next->content;
		*tokens = (*tokens)->next;
	}
	else
		flag = 5;
	if (flag == HEREDOC)
	{
		str = heredoc(str);
		heredoc_flag = 1;
	}
	if (flag != 5)
		ft_newcommand(redi, ft_strdup(str), flag);
	if (heredoc_flag)
		free(str);
	return (0);
}
