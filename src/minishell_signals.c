//
// Created by user on 12.02.2022.
//

#include "../include/minishell.h"

void	base_signal(void)
{
    signal(SIGTERM, SIG_IGN);
    signal(SIGINT, cntrl_c);
    signal(SIGQUIT, SIG_IGN);
    return ;
}

void	input_eof(void)
{
    write(2, "exit\n", 5);
    exit(0);
}

void	cntrl_c(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    errno = 1;
    return ;
}

void	cntrl_c2(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    errno = 1;
    return ;
}