/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaparic <alaparic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:24:36 by alaparic          #+#    #+#             */
/*   Updated: 2023/08/15 13:39:01 by alaparic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_export(char **env)
{
	int		i;
	char	**sort_env;

	i = 0;
	sort_env = ft_sort_matrix(env);
	while (sort_env[i])
		ft_printf("declare -x %s\n", sort_env[i++]);
}

int	invalid_value(char **env)
{
	free_matrix(env);
	ft_putstr_fd("\033[0;31mInvalid identifier\n\033[0m", 2);
	return (1);
}

char	*get_value_for_var(char *str)
{
	char	*aux;
	char	*var;

	aux = ft_strchr(str, '=');
	if (aux != 0)
		var = ft_substr(str, 0, ft_strlen(str) - ft_strlen(aux));
	else
		var = ft_strdup(str);
	return (var);
}
