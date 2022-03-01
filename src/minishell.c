//
// Created by user on 10.02.2022.
//

#include "../include/minishell.h"

//int main()
//{
//char *tmp;
//tmp[0] = '\'';
//if (tmp[0] == '\"')
//	printf("oni ravni %i",tmp[0]);
//
//	printf("oni ravni %i",tmp[0]);
//	//	printf("abcd\' sddd  \"");
//	return(0);
//}


int	main(int argc, char **argv, char **envp)
{
	t_shell minishell;

	initialization(&minishell, argc, argv);
	get_environment(&minishell, envp);
	rl_outstream = stderr;
	//The stdio stream to which Readline performs output. If NULL, Readline
	//defaults to stdout.
	base_signal();
	check_shlvl(&minishell);
	while (1)
	{
		//minishell.input = readline("\e[0;32mminishell$\e[0;39m "); chende
		// on second line 18.02.22
		minishell.input = readline(omg_minisheel);
		/** нажимаешь ctrl + d*/
		if (!(minishell.input))
			input_eof();
		/** когда это может возникнуть?*/
//		if (ft_strlen(minishell.input) == 0)
//		{
//			free(minishell.input);
//			continue;
//		}
		add_history(minishell.input);
		if (minishell_pre_parser(&minishell))
			minishell_scheduler(&minishell);
		garbage_collector(&minishell);
	}
}
