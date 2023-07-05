/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/05 16:29:27 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	quote_split(char *str, t_list **splitted)
{
	char			len;
	int				i;
	enum e_quotes	flag;
	enum e_quotes	old_flag;

	i = 0;
	flag = 0;
	old_flag = check_flag(str, i);
	while (str[i])
	{
		len = 0;
		flag = check_flag(str, i + len);
		while (flag == old_flag && str[i + len])
			flag = check_flag(str, i + ++len);
		if (old_flag != NONE)
			flag = check_flag(str, i + ++len);
		ft_lstadd_new(splitted, ft_substr(str, i, len));
		i = i + len;
		old_flag = flag;
	}
	free(str);
}

static void	parse_phrase(t_list **list, char **env)
{
	t_list			*aux;

	aux = *list;
	while (aux)
	{
		aux->content = split_quotes(aux->content, env);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list	*list)
{
	char	*str;
	char	*aux;

	str = ft_strtrim(list->content, " 	");
	while (list->next)
	{
		list = list->next;
		aux = str;
		if (list->content && ft_strtrim(list->content, " 	") != NULL)
			str = ft_strjoin(str, ft_strtrim(list->content, " 	"));
		free(aux);
	}
	return (str);
}

t_list *expand_values(t_list *args, char **env)
{
	t_list	*splitted;
	t_list	*aux;

	aux = args;
	splitted = NULL;
	while (args)
	{
		while (!args->content || ft_strlen(ft_strtrim(args->content, " 	")) < 1)
			args = args->next;
		quote_split(ft_strtrim(args->content, " 	"), &splitted);
		parse_phrase(&splitted, env);
		args->content = join_phrases(splitted);
		(free_stacks(&splitted), splitted = NULL);
		args = args->next;
	}
	return (aux);
}
