/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:39:46 by acolonne          #+#    #+#             */
/*   Updated: 2025/05/23 19:40:00 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_sq(int *i, char **text)
{
	(*i)++;
	while ((*text)[*i] && (*text)[*i] != '\'')
		(*i)++;
	if ((*text)[*i] == '\'')
		(*i)++;
}

void	expand_variable(t_minishell *minishell, char **text, int *i)
{
	char	*var;
	char	*expand;
	int		len;
	int		is_exit_code;

	var = get_var(*text, *i + 1);
	if (!var)
	{
		(*i)++;
		return ;
	}
	is_exit_code = (!ft_strcmp(var, "?"));
	if (is_exit_code)
		expand = ft_itoa(minishell->exit_code);
	else
		expand = ft_getenv(minishell->env, var);
	*text = replace_var(*text, expand, var, *i);
	len = ft_strlen(expand);
	free(var);
	if (is_exit_code)
		free(expand);
	*i += len;
}

void	expand_text(t_minishell *minishell, char **text)
{
	int		i;

	i = 0;
	while (*text && (*text)[i])
	{
		check_heredoc_expand(*text, &i);
		if ((*text)[i] == '\'')
			expand_sq(&i, text);
		else if ((*text)[i] == '"')
			handle_double_quotes(minishell, text, &i);
		else if ((*text)[i] == '$' && (*text)[i + 1])
			expand_variable(minishell, text, &i);
		else
			i++;
	}
}

int	read_heredoc(int fd, char *delimiter, t_minishell *minishell, int is_expand)
{
	char	*buf;

	buf = 0;
	while (1)
	{
		buf = readline("<*_*> ");
		if (!buf)
		{
			print_error("heredoc error\n");
			return (0);
		}
		if (!ft_strcmp(delimiter, buf))
		{
			if (buf)
				free(buf);
			close (fd);
			return (1);
		}
		if (is_expand)
			expand_text(minishell, &buf);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	return (0);
}

int	heredoc(char *limiter, t_minishell *minishell, int is_expand)
{
	int	fd;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (read_heredoc(fd, limiter, minishell, is_expand) < -1)
	{
		unlink(".heredoc");
		return (-1);
	}
	fd = open(".heredoc", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc");
	return (fd);
}
