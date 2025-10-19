#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	memcpy(tmp, *s1, size1);
	memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, strlen(s2));
}

char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE] = "";
	char	*ret = NULL;
	char	*tmp = strchr(b ,'\n');

	while(!tmp)
	{
		if(!str_append_str(&ret, b))
			return NULL;
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if(read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if(!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
