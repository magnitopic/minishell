#include "../include/minishell.h"



/**
 * Creates the temp files that heredoc needs to function. /tmp/.heredoc_*
*/
static char	*create_file(char *str)
{
	char	*file_name;
	int		fd;
	int		i;
	char	*nbr;

	i = 0;
	while (i < 100000)
	{
		nbr = ft_itoa(i);
		file_name = ft_strjoin("/tmp/.heredoc_", nbr);
		free(nbr);
		if (access(file_name, F_OK))
			break ;
		free(file_name);
		i++;
	}
	fd = open(file_name, O_CREAT | O_RDWR, 0644);
	write(fd, str, ft_strlen(str));
	close(fd);
	return (file_name);
}

char	*heredoc(char *key_word)
{
	char	*input;
	char	*str;
	char	*aux;
	char	*prompt;

	signal(SIGINT, SIG_IGN);
	str = ft_calloc(1, 1);
	prompt = get_heredoc_prompt(key_word);
	while (1)
	{
		input = readline(prompt);
		if (input == NULL || ft_strcmp(input, key_word) == 0)
			break ;
		aux = ft_strjoin(str, input);
		str = ft_strjoin(aux, "\n");
		(free(aux), free(input));
	}
	aux = str;
	str = create_file(str);
	free(prompt);
	free(input);
	(free(aux), signal(SIGINT, signal_handler));
	return (str);
}

int	main(int argc, char const *argv[])
{
	heredoc("yes");
	return 0;
}
