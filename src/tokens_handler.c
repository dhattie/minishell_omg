//
// Created by user on 13.02.2022.
//

#include "../include/minishell.h"

int	handle_pipe(t_shell *minishell, int *i)
{
    char	*ret;

	//изменения №5
    //ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    minishell->apps->token = IS_PIPE;
    add_application(minishell);

	skip_space_tab(minishell, i);
//изменения 2
//    while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
//    	|| minishell->input[*i + 1] == '\t'))
//        ++(*i);
// Изменения №1
	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));
// Было изначально
//    if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));
// изменения №3
//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);
	ret = check_for_data(minishell, *i);

    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    minishell->launch_method = 1;
    return (0);
}

int	redirect_output(t_shell *minishell, int *i)
{
    char	*ret;

   // ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    minishell->apps->token = TOKEN_REDIRECT_OUTPUT;

	skip_space_tab(minishell, i);
//	while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
//                                         || minishell->input[*i + 1] == '\t'))
//        ++(*i);

	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));

//    if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));
	ret = check_for_data(minishell, *i);

//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);
    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}

int	redirect_output_append(t_shell *minishell, int *i)
{
    char	*ret;

  //  ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    minishell->apps->token = TOKEN_REDIRECT_OUTPUT_APPEND;
    ++(*i);

// Изменения 1
	skip_space_tab(minishell, i);
//    while (minishell->input[*i] != 0 && (minishell->input[*i + 1] == ' '
//                                         || minishell->input[*i + 1] == '\t'))
//        ++(*i);

	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));

// Изменение 2
//    if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));

//изменения 3
	ret = check_for_data(minishell, *i);
//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);
    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}

int	redirect_input(t_shell *minishell, int *i)
{
    char	*ret;

 //   ret = NULL;
    if (*i != 0)
        expand_argv(minishell, i);
    minishell->apps->token = TOKEN_REDIRECT_INPUT;

// изменение 1
	skip_space_tab(minishell, i);
//	while (minishell->input[*i + 1] == ' ' || minishell->input[*i + 1] == '\t')
//        ++(*i);

// изменения 2
	if (ft_strchr("0|<>&", (int)minishell->input[*i + 1]))
		return (syntax_error(minishell, minishell->input + *i + 1, 1));

//	if (minishell->input[*i + 1] == 0 || minishell->input[*i + 1] == '|'
//        || minishell->input[*i + 1] == '<' || minishell->input[*i + 1] == '>'
//        || minishell->input[*i + 1] == '&')
//        return (syntax_error(minishell, minishell->input + *i + 1, 1));

// изменение 3
	ret = check_for_data(minishell, *i);
//    if (minishell->input[*i] != 0 && minishell->input[*i + 1] != 0)
//        ret = ft_strdup(minishell->input + *i + 1);
    (*i) = -1;
    free(minishell->input);
    minishell->input = ret;
    return (0);
}

int	tokens_handler(t_shell *minishell, int *i)
{
	if (minishell->input[*i] == '|')
    {
        if (minishell->input[*i + 1] == '|')
            return (handle_or(minishell, i));
        return (handle_pipe(minishell, i));
    }
    else if (minishell->input[*i] == '>')
    {
        if (minishell->input[*i + 1] == '>')
            return (redirect_output_append(minishell, i));
        return (redirect_output(minishell, i));
    }
    else if (minishell->input[*i] == '<')
    {
        if (minishell->input[*i + 1] == '<')
            return (heredoc(minishell, i));
        return (redirect_input(minishell, i));
    }
    else if (minishell->input[*i] == '&')
    {
        if (minishell->input[*i + 1] == '&')
            return (double_ampersand(minishell, i));
        return (single_ampersand(minishell, i));
    }
    return (0);
}
