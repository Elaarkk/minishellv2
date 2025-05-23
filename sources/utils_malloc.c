/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguilleu <aguilleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:56:08 by aguilleu          #+#    #+#             */
/*   Updated: 2025/05/23 13:58:27 by aguilleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*t;

	i = 0;
	t = (unsigned char *)s;
	while (i < n)
	{
		t[i] = (unsigned char)c;
		i++;
	}
	return ((void *)t);
}

char	**dup_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	*goodmalloc(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*tmp;

	i = ft_strlen(s);
	if (i <= start || len == 0)
		tmp = malloc(1);
	else if (i - start < len)
		tmp = malloc(sizeof(char) * (i - start + 1));
	else
		tmp = malloc(sizeof(char) * (len + 1));
	return (tmp);
}

char	**get_path(char **env)
{
	int		i;
	char	**path_list;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_list = ft_split(&env[i][5], ':');
			return (path_list);
		}
		i++;
	}
	return (0);
}

char	*ft_getenv(char **env, char *loc)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(loc);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], loc, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}
