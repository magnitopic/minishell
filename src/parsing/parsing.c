/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarabia <jsarabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/22 14:51:08 by jsarabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the raw user input onto a list where each element is
 * a command
*/

char	**order_values(char	**old_arr)
{
	t_vars	new;

	new.i = 0;
	new.j = 0;
	while (old_arr[new.j])
		new.j++;
	new.arr = ft_calloc(new.j + 1, sizeof(char *));
	new.j = 0;
	while (old_arr[new.j])
	{
		if (old_arr[new.j][0] != '<' && old_arr[new.j][0] != '>' && \
	(new.j < 1 || (old_arr[new.j - 1][0] != '<'
			&& old_arr[new.j - 1][0] != '>')))
		{
			printf("JAJA, %s arr[%d][0] = %c\n", old_arr[new.j], new.j, old_arr[new.j][0]);
			new.arr[new.i] = ft_substr(old_arr[new.j], 0,
					ft_strlen(old_arr[new.j]));
			new.i++;
		}
		new.j++;
	}
	new.j = 0;
	while (old_arr[new.j])
	{
		if (old_arr[new.j][0] == '<' || old_arr[new.j][0] == '>')
		{
			new.arr[new.i] = ft_substr(old_arr[new.j], 0, ft_strlen(old_arr[new.j]));
			new.i++;
		}
		new.j++;
	}
	free_matrix(old_arr);
	return (new.arr);
}

t_list	*split_commands(char *input, t_list *com)
{
	char			*str;
	char			*temp;
	int				i;
	int				old_pos;

	str = input;
	i = 0;
	old_pos = 0;
	while (input[i])
	{
		if (check_flag(input, i) == NONE && input[i] == 124)
		{
			temp = ft_substr(str, old_pos, i - old_pos);
			if (com == NULL)
				com = ft_lstnew(temp);
			else
				ft_lstadd_back(&com, ft_lstnew(temp));
			str = input;
			old_pos = i;
		}
		i++;
	}
	ft_lstadd_back(&com, ft_lstnew(str + old_pos));
	return (com);
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	commands = NULL;
	paths = NULL;
	if (check_unclosed_quotes(input))
	{
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return ;
	}
	commands = split_commands(input, commands);
	aux = commands;
	while (aux)
	{
		aux->content = split_words(aux->content);
		//aux->content = order_values(aux->content);
		aux->content = expand_values(aux->content, env);
		int i = 0;
		printf("\033[0;35mParsed:\033[0m\n");
		while (((char **)aux->content)[i])
			printf("%s\n", ((char **)aux->content)[i++]);
		printf("\033[0;35m--------------------\033[0m\n");
		aux = aux->next;
	}
	aux = commands;
	/*while (commands)
	{
		execution(commands->content, paths, env);
		commands = commands->next;
	}
	free_stacks(&aux);*/
}
