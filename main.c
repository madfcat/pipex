/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:41:30 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/12 21:21:04 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	execute(t_store *s, char *envp[], char *cmd)
{
	if (execve(s->executable, s->exec_args, envp) == -1)
	{
		print_error_msg(s->shell_name, 22, cmd);
		exit(EXIT_FAILURE);
	}
}

void	handle_child_process(t_store *s, char *argv[], char *envp[])
{
	s->exec_args = NULL;
	if (access(argv[1], R_OK) == -1)
	{
		print_error_msg(s->shell_name, 2, argv[1]);
		exit(EXIT_SUCCESS);
	}
	if (dup2(s->fd, STDIN_FILENO) == -1)
	{
		close(s->fd);
		print_error_msg(s->shell_name, 9, "");
		exit(EXIT_FAILURE);
	}
	if (dup2(s->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		print_error_msg(s->shell_name, 9, "");
		exit(EXIT_FAILURE);
	}
	close(s->pipe_fd[1]);
	close(s->pipe_fd[0]);
	s->executable = find_exec_path(s->paths, s->cmd1[0], s->shell_name);
	free_paths(s->paths);
	parse_exec_args(&s->exec_args, s->cmd1, s->executable);
	execute(s, envp, s->cmd1[0]);
}

void	handle_parent_process(t_store *s, char *argv[], char *envp[])
{
	s->exec_args = NULL;
	close(s->pipe_fd[1]);
	if (dup2(s->pipe_fd[0], STDIN_FILENO) == -1)
	{
		print_error_msg(s->shell_name, 9, "");
		exit(EXIT_FAILURE);
	}
	close(s->pipe_fd[0]);
	s->executable = find_exec_path(s->paths, s->cmd2[0], s->shell_name);
	free_paths(s->paths);
	parse_exec_args(&s->exec_args, s->cmd2, s->executable);
	s->fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (s->fd_out == -1)
	{
		print_error_msg(s->shell_name, 9, "");
		exit(EXIT_FAILURE);
	}
	if (dup2(s->fd_out, STDOUT_FILENO) == -1)
	{
		close(s->fd_out);
		print_error_msg(s->shell_name, 9, "");
		exit(EXIT_FAILURE);
	}
	close(s->fd_out);
	execute(s, envp, s->cmd2[0]);
}

void	fork_main(t_store *s, char *argv[], char *envp[])
{
	s->fd = open(argv[1], O_RDONLY);
	s->pid = fork();
	if (s->pid < 0)
	{
		print_error_msg(s->shell_name, 10, "");
		exit(10);
	}
	if (s->pid == 0)
		handle_child_process(s, argv, envp);
	else
		handle_parent_process(s, argv, envp);
	free(s->executable);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_store	s;

	if (argc <= 4 || argc > 5)
		exit(EXIT_FAILURE);
	s.paths = NULL;
	s.paths = find_paths(envp, s.shell_name);
	s.shell_name = find_shell_name(envp);
	if (argc == 5)
	{
		s.cmd1 = split_command(argv[2], s.shell_name);
		s.cmd2 = split_command(argv[3], s.shell_name);
		if (pipe(s.pipe_fd) == -1)
		{
			print_error_msg(s.shell_name, 9, "");
			exit(EXIT_FAILURE);
		}
		fork_main(&s, argv, envp);
	}
	else
		free_paths(s.paths);
	return (0);
}
