/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:45:42 by nkiefer           #+#    #+#             */
/*   Updated: 2025/02/01 14:56:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../LIBFT/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

// Structure principale pour pipex
typedef struct s_pipex
{
	int		pipefd[2];		// Descripteurs pour le pipe
	char	**envlp;		// Environnement
	char	*outfile_name;	// Nom du fichier de sortie
}				t_pipex;

typedef struct s_exec
{
	int			infile_fd;
	int			outfile_fd;
	int			status;
	pid_t		pid1;
	pid_t		pid2;
}				t_exec;

typedef struct s_child_data
{
	int			input_fd;
	int			output_fd;
	char		*cmd;
}				t_child;

typedef struct s_arg
{
	char		**args;
	const char	*str;
	int			start;
	int			end;
}				t_arg_data;

// Prototypes des fonctions
void			error_exit(const char *message, char **to_free);
void			error_msg(char **cmd_args, char *msg, int code);
void			close_pipes(t_pipex *pipex);
// void	wait_children(t_exec *exec);
void			init_pipex(t_pipex *pipex, char **envlp, char *outfile_name);
void			run_pipex(t_pipex *pipex, char **argv);
void			handle_input(t_exec *exec, char *filename);
void			execute_command(char *cmd, char **envp);
void			child_process(t_pipex *pipex, t_exec *exec,
					t_child *child_data);
void			first_child(t_pipex *pipex, t_exec *exec, char *cmd);
void			second_child(t_pipex *pipex, t_exec *exec, char *cmd);
char			*find_command_path(char *cmd, char **envp);
char			*pwd_path(char *cmd, char **envp);
char			*get_env_path(char **envlp, const char *name);
char			*join_with_slash(const char *prefix, const char *suffix);
char			*get_valid_path(char *cmd, char **envp);
char			*search_in_paths(char **paths, char *cmd);
int				handle_quote(const char *str, int i, char quote);
int				skip_whitespace(const char *str, int pos);
int				skip_arg(const char *str, int pos);

// Fonctions utilitaires
void			ft_free_split(char **split);
void			ft_putstr_fd(char *str, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(const char *s1, const char *s2);
char			**ft_split(const char *s, char c);
char			**split_command(const char *str);
void			initialize_positions_forsplitdemesc(int pos[3]);

#endif
