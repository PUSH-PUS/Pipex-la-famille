/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:45:49 by nkiefer           #+#    #+#             */
/*   Updated: 2025/01/31 16:03:32 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_env_path(char **envlp, const char *name)
{
	int	i;

	i = 0;
	while (envlp[i])
	{
		if (ft_strncmp(envlp[i], name, ft_strlen(name)) == 0)
			return (envlp[i] + ft_strlen(name));
		i++;
	}
	return (NULL);
}

char	*join_with_slash(const char *prefix, const char *suffix)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(prefix, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

char	*get_valid_path(char *cmd, char **envp)
{
	char	*path;

	path = pwd_path(cmd, envp);
	if (path && access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = join_with_slash(paths[i], cmd);
		if (!full_path)
			return (ft_free_split(paths), NULL);
		if (access(full_path, F_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
	}
	return (ft_free_split(paths), NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_path(envp, "PATH=");
	if (!path_env)
		return (get_valid_path(cmd, envp));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
