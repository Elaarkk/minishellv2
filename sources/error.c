/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:40:22 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/20 15:11:23 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all_fds(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->infile)
		{
			if (tmp->infile_fd > -1)
				close(tmp->infile_fd);
		}
		if (tmp->outfile)
		{
			if (tmp->outfile_fd > -1)
				close(tmp->outfile_fd);
		}
		tmp = tmp->next;
	}
}

void	free_all_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	if (split)
		free(split);
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->cmd)
	{
		close_all_fds(minishell->cmd);
		free_all_cmd(&minishell->cmd);
	}
	if (minishell->env)
		free_all_split(minishell->env);
	if (minishell->path)
		free_all_split(minishell->path);
	if (minishell->prompt)
		free_all_prompt(&minishell->prompt);
}

void	print_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}
