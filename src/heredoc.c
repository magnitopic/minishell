/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:22:26 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/08 15:29:50 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*heredoc(char *key_word)
{
	char	*prompt;
	char	*line;
	char	*src;
	char	*aux;

	prompt = ft_strjoin(ft_strjoin("Heredoc:", key_word), " $");
	src = readline(prompt);
	while (ft_strncmp(src, key_word, ft_strlen(src)) != 0)
	{
		aux = src;
		line = readline(prompt);
		src = ft_strjoin(src, line);
		free(aux);
		free(line);
	}
	return (src);
}

/* int	main(int argc, char **argv)
{
	printf("%s", heredoc("yes"));
	return (0);
} */