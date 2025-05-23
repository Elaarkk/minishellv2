/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolonne <acolonne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:04:18 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 16:11:00 by acolonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_identifier_unset(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!((str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= 'a' && str[0] <= 'z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	find_loc_index(char **env, char *loc)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(loc);
	while (env[i])
	{
		if (!ft_strncmp(env[i], loc, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	remove_env_var(char ***env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i == index)
			free((*env)[i]);
		else
			new_env[j++] = (*env)[i];
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
}

int	ft_unset(t_cmd *cmd, char ***env)
{
	int	i;
	int	index;

	i = 1;
	while (cmd->arg[i])
	{
		if (!is_valid_identifier_unset(cmd->arg[i]))
		{
			printf("unset: `%s': not a valid identifier\n", cmd->arg[i]);
			return (2);
		}
		else
		{
			index = find_loc_index(*env, cmd->arg[i]);
			if (index != -1)
				remove_env_var(env, index);
		}
		i++;
	}
	return (0);
}
