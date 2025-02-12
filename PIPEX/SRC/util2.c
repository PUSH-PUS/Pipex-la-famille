/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:24:39 by nkiefer           #+#    #+#             */
/*   Updated: 2025/01/31 16:26:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*pwd_path(char *cmd, char **envlp)
{
	char	*pwd;
	char	*full_path;

	pwd = get_env_path(envlp, "PWD=");
	if (!pwd)
		return (NULL);
	full_path = join_with_slash(pwd, cmd);
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

void	ft_free_split(char **ft_split)
{
	int	i;

	i = 0;
	if (!ft_split)
		return ;
	while (ft_split[i])
	{
		free(ft_split[i]);
		i++;
	}
	free(ft_split);
}

int	handle_quote(const char *str, int i, char quote)
{
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	skip_whitespace(const char *str, int pos)
{
	while (str[pos] && (str[pos] == ' ' || str[pos] == '\t'))
		pos++;
	return (pos);
}

int	skip_arg(const char *str, int pos)
{
	while (str[pos] && !(str[pos] == ' ' || str[pos] == '\t'))
	{
		if (str[pos] == '\'' || str[pos] == '"')
			pos = handle_quote(str, pos, str[pos]);
		else
			pos++;
	}
	return (pos);
}
