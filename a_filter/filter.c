#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ft_strncmp(char *p, char *word, int n) {
	int i = 0;
	while (i < n && p[i] && word[i] && p[i] == word[i])
		i++;
	if (i == n)
		return 0;
	return p[i] - word[i];
}

char *readline() {
	int buffer_size = 1024;
	char *buffer = malloc(buffer_size);
	if (!buffer)
		return (perror("failed allocation buffer"), NULL);

	char *input = malloc(1);
	if (!input)
		return (perror("failed allocation input"), free(buffer), NULL);
	input[0] = '\0';

	int size_total = 0;
	int b_read;
	while ((b_read = read(0, buffer, buffer_size)) > 0) {
		char *tmp = realloc(input, size_total + b_read + 1);
		if (!tmp)
			return (perror("failed allocation TMP"), free(buffer), free(input), NULL);
		input = tmp;
		memcpy(input + size_total, buffer, b_read);
		size_total += b_read;
		input[size_total] = '\0';
	}

	if (b_read < 0)
		perror("ERROR read\n");

	free(buffer);
	return input;
}

int main(int ac, char **av) {
	if (ac != 2)
		return (printf("ERROR args\n"), 1);

	char *word = av[1];
	int s_word = strlen(word);
	if (s_word == 0)
		return (printf("ERROR empty word\n"), 1);

	char *input = readline();
	if (!input)
		return 1;

	char *ptr = input;
	while (*ptr) {
		if (ft_strncmp(ptr, word, s_word) == 0) {
			for (int i = 0; i < s_word; i++)
				ptr[i] = '*';
			ptr += s_word;
		} else {
			ptr++;
		}
	}
	printf("%s", input);
	free(input);
	return 0;
}
