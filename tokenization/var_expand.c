/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:39:55 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 13:48:08 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*unvalid_var(char *text, int *i, char *ret)
{
	if (text[*i] == '"' || text[*i] == '\'')
		ret = malloc(1);
	else if ((text[*i] >= '0' && text[*i] <= '9')
		|| (!is_valid_var_char(text[*i]) || text[*i] == '\0'))
		ret = malloc(2);
	if (!ret)
		return (NULL);
	if (text[*i] == '"' || text[*i] == '\'')
	{
		ret[0] = '\0';
		return (ret);
	}
	if (text[*i] >= '0' && text[*i] <= '9')
	{
		ret[0] = text[*i];
		ret[1] = '\0';
		return (ret);
	}
	if (!is_valid_var_char(text[*i]) || text[*i] == '\0')
	{
		ret[0] = '$';
		ret[1] = '\0';
		return (ret);
	}
	return (NULL);
}

char	*get_var(char *text, int i)
{
	char	*var;
	char	*ret;
	int		len;
	int		start;

	var = NULL;
	ret = NULL;
	len = 0;
	start = i;
	ret = unvalid_var(text, &i, ret);
	while (text && text[i] && is_valid_var_char(text[i]))
	{
		len++;
		i++;
	}
	var = malloc(len + 1);
	if (!var)
		return (NULL);
	ft_strlcpy(var, &text[start], len + 1);
	return (var);
}

int	check_var(char *new)
{
	if (new[0] == '\0')
	{
		free(new);
		return (0);
	}
	return (1);
}

char	*cpy_var_start(int before, char *new, char *text, int *j)
{
	while (*j < before)
	{
		new[*j] = text[*j];
		(*j)++;
	}
	return (new);
}

char	*replace_var(char *text, char *expand, char *var, int i)
{
	int		before;
	int		after;
	char	*new;
	int		k;
	int		j;

	j = 0;
	before = i;
	k = 0;
	after = before + ft_strlen(var) + 1;
	new = malloc(ft_strlen(text) - ft_strlen (var) + ft_strlen(expand));
	if (!new)
		free(text);
	if (!new)
		return (0);
	new = cpy_var_start(before, new, text, &j);
	while (expand && expand[k])
		new[j++] = expand[k++];
	while (text && text[after])
		new[j++] = text[after++];
	free(text);
	new[j] = '\0';
	if (check_var(new) == 0)
		return (0);
	return (new);
}
