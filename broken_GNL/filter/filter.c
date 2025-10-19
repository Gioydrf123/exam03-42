/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 19:18:24 by gmu               #+#    #+#             */
/*   Updated: 2025/10/18 19:18:30 by gmu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*read_stdin_to_string(void)
{
	int		buffer_size;
	char	*buffer;
	int		total_read;
	int		bytes_read;
	char	*new_buffer;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return (NULL);
	total_read = 0;
	while ((bytes_read = read(0, buffer, buffer_size)) > 0)
	{
		total_read += bytes_read;
		if (total_read >= buffer_size)
		{
			buffer_size *= 2;
			new_buffer = realloc(buffer, sizeof(char) * buffer_size);
			if (!new_buffer)
			{
				free(buffer);
				return (NULL);
			}
			buffer = new_buffer;
		}
	}
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[total_read] = '\0';
	return (buffer);
}

int	main(int argc, char **argv)
{
	char	*str1;
	char	*string;
	int		i;

	if (argc != 2)
		return (1);
	str1 = argv[1];
	string = read_stdin_to_string();
	if (!argv[1])
	{
		printf("%s", string);
		return (0);
	}
	i = 0;
	while (string[i])
	{
		if (strchr(str1, string[i]))
			string[i] = '*';
		++i;
	}
	printf("%s", string);
	free(string);
	return (0);
}
