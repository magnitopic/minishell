/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 12:21:13 by alaparic          #+#    #+#             */
/*   Updated: 2023/06/08 13:19:13 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * This function separates the different commands on to a list
*/
static void	get_commands(char *input, t_list **com)
{
	enum e_quotes	flag;
	char			*str;
	char			*temp;

	str = input;
	while (*input)
	{
		flag = check_flag(input, 0, flag);
		if (flag == NONE && (*input == 124
				|| *input == 62 || *input == 60))
		{
			temp = ft_substr(str, 0, ft_strlen(str) - ft_strlen(input));
			if (*com == NULL)
				*com = ft_lstnew(temp);
			else
				ft_lstadd_back(com, ft_lstnew(temp));
			str = input;
			if (flag == NONE && (*input == 124
					|| *input == 62 || *input == 60))
				input++;
		}
		input++;
	}
	ft_lstadd_back(com, ft_lstnew(str));
}

void	parsing(char *input, char **paths, char **env)
{
	t_list	*commands;
	t_list	*aux;

	((void)paths, (void)env);
	commands = NULL;
	if (check_quotes(input) == -1)
	{
		ft_putstr_fd("\033[0;31mError: Unclosed quotes\033[0;\n", 2);
		return ;
	}
	get_commands(input, &commands);
	aux = commands;
	while (aux)
	{
		printf("command: %s\n", aux->content);
		aux->content = parse_words(aux->content);
		int i = 0;
		while (((char **)aux->content)[i]){
			printf("|%s|\n", ((char **)aux->content)[i]);
			expand_var(((char **)aux->content)[i], env);
			i++;
		}
		aux = aux->next;
	}
	while (commands)
	{
		execution(commands->content, paths, env);
		commands = commands->next;
	}
	//free_stacks(&commands);
}
