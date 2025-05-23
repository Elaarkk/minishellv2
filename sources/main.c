/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:43:21 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 18:14:09 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	g_signal_pid;

void	logo(void)
{
	printf("\033[0;32m");
	printf(" _                                ");
	printf("   _       _     _          _ _       \n");
	printf("| |                                ");
	printf(" (_)     (_)   | |        | | |      \n");
	printf("| |__  _ __ ___  _ __ ___  _ __ _");
	printf("__  _ _ __  _ ___| |__   ___| | |      \n");
	printf("| '_ \\| '_ ` _ \\| '_ ` _ \\| '_ ` ");
	printf("_ \\| | '_ \\| / __| '_ \\ / _ \\ | |      \n");
	printf("| | | | | | | | | | | | | | | | ");
	printf("| | | | | | | \\__ \\ | | |  __/ | |_ _ _ \n");
	printf("|_| |_|_| |_| |_|_| |_| |_|_| |_| |");
	printf("_|_|_| |_|_|___/_| |_|\\___|_|_(_|_|_)\n\n");
	printf("\033[0m");
}

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->prompt = 0;
	minishell->cmd = 0;
	minishell->env = dup_env(env);
	minishell->path = get_path(minishell->env);
	minishell->exit_code = 0;
}

char	*handle_readline(t_minishell *minishell)
{
	char	*content;

	content = 0;
	if (isatty(fileno(stdin)))
		content = readline("minishell-1.37b$ ");
	if (!content)
	{
		free_minishell(minishell);
		printf("exit\n");
		exit(0);
	}
	add_history(content);
	return (ft_strdup(content));
}

void	main_loop(t_minishell *minishell, struct sigaction *sa)
{
	char	*content;

	while (1)
	{
		sigaction(SIGINT, sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		content = handle_readline(minishell);
		if (!check_quotes(content))
		{
			free(content);
			continue ;
		}
		expand_text(minishell, &content);
		minishell->prompt = cut_prompt(content);
		free(content);
		if (minishell->prompt)
			analyse_prompt(minishell);
		minishell->path = get_path(minishell->env);
		g_signal_pid = 0;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell			minishell;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	logo();
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	g_signal_pid = 0;
	init_minishell(&minishell, env);
	main_loop(&minishell, &sa);
	return (0);
}
