/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:22:26 by alaparic          #+#    #+#             */
/*   Updated: 2023/07/10 02:08:30 by alaparic         ###   ########.fr       */
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
	line = readline(prompt);
	src = ft_strdup(line);
	while (ft_strncmp(line, key_word, ft_strlen(line)) != 0)
	{
		free(line);
		aux = src;
		line = readline(prompt);
		src = ft_strjoin(src, line);
		free(aux);
		aux = src;
		src = ft_strjoin(src, "\n");
		free(aux);
	}
	free(line);
	return (src);
}

int	main(int argc, char **argv)
{
	printf("%s", heredoc("yes"));
	return (0);
}
