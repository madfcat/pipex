/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:41:30 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/08 18:29:23 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.thegeekstuff.com/2010/10/linux-error-codes/
/**
 * In macOS, executables can be stored in various directories, and the location of these directories is specified in the system's PATH environment variable. Common directories for storing executables in macOS include:

/bin: Core system binaries essential for system boot and repair.
/usr/bin: User command binaries.
/usr/local/bin: User-installed binaries (this directory is not part of the system default PATH, but it's commonly used for user-installed software).
/sbin: System binaries for system administration.
/usr/sbin: System binaries for system administration, not intended for normal user use.
/usr/local/sbin: User-installed system administration binaries (similar to /usr/local/bin, not part of the system default PATH).


https://www.geeksforgeeks.org/fork-system-call/
https://www.geeksforgeeks.org/pipe-system-call/
https://opensource.apple.com/source/Libc/Libc-825.25/gen/errlst.c

*/
#include "ft_pipex.h"

int get_file_size(char *file_name)
{
	int fd;
	char buffer[1];
	int result;
	int read_bytes;

	fd = open(file_name, O_RDONLY);
	result = 0;
	while (1)
	{
		read_bytes = read(fd, buffer, 1);
		if (read_bytes == 0)
			return (result);
		else if (read_bytes < 0)
		{
			ft_printf("%s\n", strerror(2));
			return (-1);
		}
		result += read_bytes;
	}
	close(fd);
}

char *read_file(char *file_name)
{
	int fd;
	int file_size;
	char *read_file;
	int read_bytes;

	fd = open(file_name, O_RDONLY);
	file_size = get_file_size(file_name);
	read_file = (char *)malloc(file_size);
	read_bytes = read(fd, read_file, file_size);
	close(fd);
	return (read_file);
}

void free_paths(char **paths)
{
	int j;

	j = ft_strlen((char *)paths);
	while (j >= 0)
	{
		free(paths[j]);
		j--;
	}
	free(paths);
}

char **find_paths(char *envp[])
{
	char *line;
	char **paths;

	int i = 0;
	while (envp[i] != NULL)
	{
		// ft_printf("%s\n", envp[i]);
		line = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i]));
		if (line)
		{
			// ft_printf("%p\n", line);
			// ft_printf("Found!\n");
			// ft_printf("%s\n", envp[i]);
			paths = ft_split(line + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char *find_exec_path(char **paths, char *name)
{
	char *executable;
	char *temp;

	// executable = NULL;
	if (!name || !name[0])
		return (NULL);
	while (*paths)
	{
		executable = ft_strdup(*paths);
		temp = executable;
		executable = ft_strjoin(temp, "/");
		free(temp);
		temp = executable;
		executable = ft_strjoin(temp, name);
		free(temp);
		// ft_printf("%s\n", executable);
		// ft_printf("%d\n", access(executable, X_OK));

		// ft_putstr(executable, 1);
		// ft_putstr("\n", 1);

		if (access(executable, X_OK) == 0)
		{
			// ft_printf("%s\n", *paths);
			// ft_printf("%s\n", executable);
			return (executable);
		}
		paths += 1;
		free(executable);
	}

	/* 	executable = ft_strdup("/Users/vshchuki/Documents/projects/pipex/");
		temp = executable;
		executable = ft_strjoin(temp, name); */

	// ft_printf("%s\n", executable);
	/* 	if (access(executable, X_OK) == 0)
		{
			return (executable);
		} */

	// ft_putstr(executable, 1);
	// ft_putstr("\n", 1);

	return (NULL);
}

char *find_shell_name(char *envp[])
{
	char *line;
	char *shell_name;

	int i = 0;
	while (envp[i] != NULL)
	{
		// ft_printf("%s\n", envp[i]);
		line = ft_strnstr(envp[i], "SHELL=", ft_strlen(envp[i]));
		if (line)
		{
			shell_name = ft_strrchr(envp[i], '/') + 1;
			return (shell_name);
		}
		i++;
	}
	return (NULL);
}

void real_join(char **string1, char *string2)
{

	char *temp;

	temp = *string1;
	*string1 = ft_strjoin(temp, string2);
	free(temp);
}

/**
 * For example, str is a filename for No such file or directory error
 */
void print_error_msg(char *shell_name, int error_code, char *str)
{
	char *error_msg;
	int i;
	char *final_msg;

	// ft_printf("Error!\n");
	error_msg = ft_strdup(strerror(error_code));

	// for zsh
	if (ft_strncmp(shell_name, "zsh", ft_strlen(shell_name)) == 0)
	{
		i = 0;
		while (error_msg[i])
		{
			error_msg[i] = ft_tolower(error_msg[i]);
			i++;
		}
		final_msg = ft_strjoin(shell_name, ": ");
		/* 			temp = final_msg;
					final_msg = ft_strjoin(temp, error_msg);
					free(temp); */
		real_join(&final_msg, error_msg);
		/* 			temp = final_msg;
					final_msg = ft_strjoin(temp, ": ");
					free(temp); */
		real_join(&final_msg, ": ");
		/* 			temp = final_msg;
					final_msg = ft_strjoin(temp, str);
					free(temp); */
		real_join(&final_msg, str);
		/* 			temp = final_msg;
					final_msg = ft_strjoin(temp, "\n");
					free(temp); */
		real_join(&final_msg, "\n");

		// dprintf(2, "%s: %s: %s\n", shell_name, error_msg, str);
		// printf("%s: %s: %s\n", shell_name, error_msg, str);
	}
	else
	{
		final_msg = ft_strjoin("-", shell_name);
		/* 		temp = final_msg;
				final_msg = ft_strjoin(temp, ": ");
				free(temp); */
		real_join(&final_msg, ": ");
		/* 		temp = final_msg;
				final_msg = ft_strjoin(temp, error_msg);
				free(temp); */
		real_join(&final_msg, error_msg);
		/* 		temp = final_msg;
				final_msg = ft_strjoin(temp, ": ");
				free(temp); */
		real_join(&final_msg, ": ");
		/* 		temp = final_msg;
				final_msg = ft_strjoin(temp, str);
				free(temp); */
		real_join(&final_msg, str);
		/* 		temp = final_msg;
				final_msg = ft_strjoin(temp, "\n");
				free(temp); */
		real_join(&final_msg, "\n");
		// dprintf(2, "-%s: %s: %s\n", shell_name, str, error_msg);
		// printf("-%s: %s: %s\n", shell_name, str, error_msg);
	}
	ft_putstr(final_msg, 2);
	free(error_msg);
	free(final_msg);
}

//	argv[1]		argv[2]		argv[3]		argv[4]
//	file1		cmd1		cmd2		file2

int main(int argc, char *argv[], char *envp[])
{
	// char *file;
	int fd;
	char *executable;
	char **paths;
	int pipe_fd[2];
	pid_t pid;
	// char *exec_args[3];
	char **exec_args;
	char **cmd1;
	char **cmd2;
	char *shell_name;
	int i;

	// int status;

	/* 	char *temp;
		char *cmd1;
		int len; */

	/* file = read_file(argv[1]); */
	/* 	int i = 0;
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		} */
	if (argc <= 4)
	{
		exit(1);
	}
	paths = find_paths(envp);
	shell_name = find_shell_name(envp);
	if (argc == 5)
	{
		if (access(argv[1], R_OK) == -1)
		{
			// perror("file read");
			// perror(shell_name);
			print_error_msg(shell_name, 2, argv[1]);
			exit(0);
		}
		cmd1 = split_command(argv[2]);
		cmd2 = split_command(argv[3]);

		if (pipe(pipe_fd) == -1)
		{
			// perror("pipe");
			// perror(shell_name);
			print_error_msg(shell_name, 9, "");
			exit(EXIT_FAILURE);
		}

		fd = open(argv[1], O_RDONLY);
		// dup2(fd, pipe_fd[0]);
		// dup2(fd, STDIN_FILENO);
		pid = fork();

		if (pid == 0)
		{
			// ft_putstr_fd("child\n", 1);
			dup2(fd, STDIN_FILENO);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);

			// ft_printf("%s\n", file);

			// ft_printf("%s\n", find_path_env_var(envp) + 5);

			executable = find_exec_path(paths, cmd1[0]);
			free_paths(paths);
			// if (!executable)
			// {
			// 	free(paths);
			// 	return (1);
			// }

			// free_paths(paths);
			// ft_printf("%s\n", executable);

			exec_args = (char **)malloc((ft_strlen((char *)cmd1) + 1) * sizeof(char *));
			exec_args[0] = executable;
			i = 1;
			while (cmd1[i])
			{
				exec_args[i] = cmd1[i];
				i++;
			}
			exec_args[i] = NULL;

			if (execve(executable, exec_args, envp) == -1)
			{
				/* 				free_paths(paths);
								if (executable)
									free(executable); */
				// perror("execve");
				// perror(shell_name);
				print_error_msg(shell_name, 22, cmd1[0]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* waitpid(pid, &status, 0); */
			// ft_putstr_fd("parent\n", 1);
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			executable = find_exec_path(paths, cmd2[0]);
			free_paths(paths);

			// if (!executable)
			// {
			// 	return (1);
			// }

			// ft_printf("%s\n", executable);

			exec_args = (char **)malloc((ft_strlen((char *)cmd2) + 1) * sizeof(char *));
			exec_args[0] = executable;
			// exec_args[1] = "-w";
						i = 1;
			while (cmd2[i])
			{
				exec_args[i] = cmd2[i];
				i++;
			}
			// exec_args[1] = cmd2[1];
			exec_args[i] = NULL;
			// char *const exec_args[] = {executable, "-l", NULL};

			int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

			if (fd_out == -1)
			{
				perror("open");
				exit(EXIT_FAILURE);
			}
			if (dup2(fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2");
				close(fd_out);
				exit(EXIT_FAILURE);
			}
			close(fd_out);

			if (execve(executable, exec_args, envp) == -1)
			{
				// free_paths(paths);
				// if (executable)
				// 	free(executable);
				// perror("execve");
				// perror(shell_name);
				print_error_msg(shell_name, 22, cmd1[0]);
				exit(EXIT_FAILURE);
			}
		}
		free(executable);
	}
	else
	{
		// print_error_msg()
		free_paths(paths);
	}
	return (0);
}
