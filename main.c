/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshchuki <vshchuki@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:41:30 by vshchuki          #+#    #+#             */
/*   Updated: 2024/01/03 19:49:26 by vshchuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://www.thegeekstuff.com/2010/10/linux-error-codes/
/**
 * In macOS, executables can be stored in various directories, and the location of these directories is specified in the system's PATH environment variable. Common directories for storing executables in macOS include:

/bin: Core system binaries essential for system boot and repair.
/usr/bin: User command binaries.
/usr/local/bin: User-installed binaries (this directory is not part of the system default PATH, but it's commonly used for user-installed software).
/sbin: System binaries for system administration.
/usr/sbin: System binaries for system administration, not intended for normal user use.
/usr/local/sbin: User-installed system administration binaries (similar to /usr/local/bin, not part of the system default PATH).
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

void	free_paths(char **paths)
{
	int	j;

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
	return ((char **)0);
}

char	*find_exec_path(char **paths, char *name)
{
	char *executable;
	char *temp;

	// (void)name;
	executable = (char *)0;
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
		if (access(executable, X_OK) == 0)
		{
			// ft_printf("%s\n", *paths);
			// ft_printf("%s\n", executable);
			return (executable);
		}
		paths += 1;
		free(executable);
	}
	return (executable);
}

int main(int argc, char *argv[], char *envp[])
{
	char *file;
	char *executable;
	char **paths;
/* 	char *temp;
	char *cmd1;
	int len; */
	(void)argc;

	file = read_file(argv[1]);
	// ft_printf("%s\n", file);

	// ft_printf("%s\n", find_path_env_var(envp) + 5);
	paths = find_paths(envp);
/* 	printf("%s\n", paths[0]);
	printf("%s\n", paths[1]);
	printf("%s\n", paths[2]);
	printf("%s\n", paths[3]);
	printf("%s\n", paths[4]);
	printf("%s\n", paths[5]);
	printf("%s\n", paths[6]);
	printf("%s\n", paths[7]); */

	executable = find_exec_path(paths, "ls");
	ft_printf("%s\n", executable);
	free_paths(paths);
	free(executable);
	// executable = ft_strdup("/bin/bash");

	// temp = executable;
	// len = strlen(argv[2]);
	// cmd1 = ft_substr(argv[2], 0, len);
	// executable = ft_strjoin(temp, cmd1);
	// free(temp);

	

/* 	char *exec_args[] = { executable, "-c", argv[1], NULL };
	execve(executable, exec_args, NULL); */

	// if (fd < 0)
	// {
	// 	// perror("");
	// 	ft_printf("%s", strerror(2));
	// 	return (2);
	// }
	// ft_printf("%d", fd);

	return (0);
}
