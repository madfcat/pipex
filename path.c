/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:14:20 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/11 19:50:00 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	free_paths(char **paths)
{
	int	j;

	if (paths)
	{
		j = ft_strlen((char *)paths);
		while (j >= 0)
		{
			free(paths[j]);
			j--;
		}
	}
	free(paths);
}

char	**find_paths(char *envp[])
{
	char	*line;
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		line = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (line)
		{
			paths = ft_split(line + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*find_exec_path(char **paths, char *name)
{
	char	*executable;
	char	*temp;

	if (!name || !name[0])
		return (NULL);
	if (access(name, X_OK) == 0)
	{
		executable = ft_strdup(name);
		return (executable);
	}
	while (*paths)
	{
		executable = ft_strdup(*paths);
		temp = executable;
		executable = ft_strjoin(temp, "/");
		free(temp);
		temp = executable;
		executable = ft_strjoin(temp, name);
		free(temp);
		if (access(executable, X_OK) == 0)
			return (executable);
		paths += 1;
		free(executable);
	}
	return (NULL);
}
