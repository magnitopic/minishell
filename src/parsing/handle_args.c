/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:36:00 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/15 17:20:19 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: Finish function for all use cases
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
		if (!*splitted)
			*splitted = ft_lstnew(ft_substr(str, i, len));
		else
			ft_lstadd_back(splitted, ft_lstnew(ft_substr(str, i, len)));
		i = i + len;
		old_flag = flag;
	}
}

static void	parse_phrase(t_list **list, char **env)
{
	t_list			*aux;
	//enum e_quotes	flag;

	aux = *list;
	while (aux)
	{
		aux->content = split_quotes(aux->content, env);
		printf("spliteao: %s\n", (char *)aux->content);
		aux = aux->next;
	}
}

static char	*join_phrases(t_list	*list)
{
	char	*str;
	char	*aux;

	str = "";
	while (list)
	{
		aux =  ft_substr(str, 0, ft_strlen(str));
		if (ft_strlen(str) > 0)
			free(str);
		str = ft_strjoin(str, list->content);
		free(aux);
		list = list->next;
	}
	return (str);
}

// TODO: 1. quote_split 2. parse_phrase -> remove quotes -> expand $ 3. join_phrases
char	**expand_values(char **args, char **env)
{
	char	**aux;
	t_list	*splitted;

	aux = args;
	splitted = NULL;
	while (*aux)
	{
		quote_split(ft_strtrim(*aux, " 	"), &splitted);
		parse_phrase(&splitted, env);
		*aux = join_phrases(splitted);
		printf("Aux: %s\n", *aux);
		(free_stacks(&splitted), splitted = NULL);
		aux++;
	}
	return (args);
}

