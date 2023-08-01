/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 14:20:52 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/01 11:36:16 by alaparic         ###   ########.fr       */
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
				else if (flag == INPUT)
					flag = HEREDOC;
				else
					return (0);
			}
			else if (str[n] == '>')
			{
				if (flag == NO)
					flag = OUTPUT;
				else if (flag == OUTPUT)
					flag = APPEND;
				else
					return (0);
			}
			else if (str[n] != '>' && str[n] != '<' && str[n] != ' ')
				flag = NO;
		}
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

int	handle_redirects(char *str, t_redi **redi, t_list **tokens)
{
	enum e_redirect	flag;

	flag = NO;
	ft_printf("alaparic\n");
	flag = flag_redi(str);
	/* if (flag == BAD_INPUT)
		return (1); */
	ft_printf("flag: %d\n", flag);
	if ((*tokens)->next != NULL)
	{
		str = (*tokens)->next->content;
		*tokens = (*tokens)->next;
	}
	else
		flag = 5;
	if (flag == HEREDOC)
		str = heredoc(str);
	if (flag != 5)
		ft_newcommand(redi, str, flag);
/* 	else
		ft_ */
	return (0);
}
