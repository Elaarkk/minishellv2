/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 19:40:23 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 19:40:49 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_heredoc_expand(char *text, int *i)
{
	if (!ft_strncmp(text, "<<", 2))
	{
		(*i) += 2;
		while (text[(*i)] && text[(*i)] == ' ')
			(*i)++;
		while (text[(*i)] && text[(*i)] != '<' && text[(*i)] != '>'
			&& text[(*i)] != '|' && text[(*i)] != ' ')
			(*i)++;
	}
}
