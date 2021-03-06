
#include "../include/minishell.h"

int	minishell_pre_parser(t_shell *minishell)
{
	int	i;

	i = 0;
	if (preparing_head(minishell) || minishell->input == NULL)
		return (0);
	add_application(minishell);
	while (minishell->input)
	{
		if (minishell_parser(minishell, &i))
			return (0);
		i++;
	}
	return (1);
}

int	preparing_head(t_shell *minishell)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (minishell->input[i] == '\t' || minishell->input[i] == ' ')
		i++;
	if (minishell->input[i] == '&' || minishell->input[i] == '|')
	{
		if (minishell->input[i] == minishell->input[i + 1])
			return (syntax_error(minishell, minishell->input + i, 2));
		return (syntax_error(minishell, minishell->input + i, 1));
	}
	if (minishell->input[i] != 0)
		ret = ft_strdup(minishell->input + i);
	free(minishell->input);
	minishell->input = ret;
	return (0);
}

int	minishell_parser(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '$')
		return (dollar_handler(minishell, i));
	else if (minishell->input[*i] == '\'')
		return (single_quote(minishell, i));
	else if (minishell->input[*i] == '\"')
		return (double_quote(minishell, i));
//изменения №1
	else if (ft_strchr(" \t0", (int)minishell->input[*i]))
		return (split_input(minishell, i));
// было изначально
//	else if (minishell->input[*i] == ' ' || minishell->input[*i] == '\t'
//			 || minishell->input[*i] == 0)
//		return (split_input(minishell, i));
	else if (tokens_handler(minishell, i))
		return (1);
	else if (wildcards_handler(minishell, i))
		return (1);
	return (0);
}



void	initialization(t_shell *minishell, int argc, char **argv)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->environment = NULL;
	minishell->child_exit_status = 0;
	minishell->apps = NULL;
	minishell->launch_method = 0;
}

