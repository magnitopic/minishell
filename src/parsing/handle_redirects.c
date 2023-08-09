/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:20:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/09 20:05:18 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_redirects(char *str)
{
	enum e_redirect	flag;
	int				n;

	n = 0;
	flag = NO;
	while (str[n])
	{
		if (check_flag(str, n) == NONE)
		{
			if ((str[n] == '<' || str[n] == '>') && !str[n + 1])
				return (0);
			else if (str[n] == '<')
			{
				if (flag == NO)
					flag = INPUT;
				else if (flag == INPUT && str[n - 1] == '<')
					flag = HEREDOC;
				else
					return (0);
			}
			else if (str[n] == '>')
			{
				if (flag == 5)
					flag = 1;
				else if (flag == OUTPUT && str[n - 1] == '>')
					flag = APPEND;
				else
					return (0);
			}
			else if (str[n] == '|' && flag != NO)
				return (0);
			else if (str[n] != '>' && str[n] != '<' && str[n] != ' ' 
				&& str[n] != '|')
				flag = NO;
		}
		if (check_flag(str, n) != NONE)
			flag = NO;
		n++;
	}
	return (1);
}

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
			if (redis->type == 0
				|| redis->type == 2)
			{
				if (open(redis->content, O_RDONLY) < 0)
				{
					g_shell->exit_stat = 1;
					ft_putstr_fd("\033[0;31mUnable to read file\033[0m\n", 2);
					return (0);
				}
			}
			if ((redis->type == 1 || redis->type == 3)
				&& (!access(redis->content, F_OK) 
					&& open(redis->content, O_WRONLY) < 0))
			{
				ft_putstr_fd("\033[0;31mPermission denied\033[0m\n", 2);
				return (0);
			}
		redis = redis->next;
		}
	commands = commands->next;
	}
	return (1);
}

int	handle_redirects(char *str, t_redi **redi, t_tokens **tokens)
{
	enum e_redirect	flag;

	flag = NO;
	flag = flag_redi(str);
	if ((*tokens)->next != NULL)
	{
		free(str);
		str = (*tokens)->next->content;
		*tokens = (*tokens)->next;
	}
	else
		flag = 5;
	if (flag == HEREDOC)
		str = heredoc(str);
	if (flag != 5)
		ft_newcommand(redi, str, flag);
	return (0);
}
