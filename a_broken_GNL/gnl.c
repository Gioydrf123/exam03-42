#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int str_append_mem(char **s1, char *s2, size_t size2) {
  size_t size1;
  char *tmp;

  if (!s1 || !s2)
    return (0);
  if (*s1)
    size1 = strlen(*s1);
  else
    size1 = 0;
  tmp = malloc(size1 + size2 + 1);
  if (!tmp)
    return (0);
  if (*s1) {
    memcpy(tmp, *s1, size1);
    free(*s1);
  }
  memcpy(tmp + size1, s2, size2);
  tmp[size1 + size2] = 0;
  *s1 = tmp;
  return (1);
}

int str_append_str(char **s1, char *s2) {
  if (!s2)
    return (0);
  return (str_append_mem(s1, s2, strlen(s2)));
}

char *get_next_line(int fd) {
  static char b[BUFFER_SIZE + 1] = "";
  char *ret = NULL;
  char *newline_pos;
  int read_ret;

  if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);

  while (1) {
    newline_pos = strchr(b, '\n');

    if (newline_pos) {
      char temp_char = newline_pos[1];
      newline_pos[1] = '\0';
      str_append_str(&ret, b);
      newline_pos[1] = temp_char;
      memmove(b, newline_pos + 1, BUFFER_SIZE - (newline_pos - b));
      break;
    }
    str_append_str(&ret, b);
    read_ret = read(fd, b, BUFFER_SIZE);
    if (read_ret <= 0) {
      if (read_ret == -1 || (ret && strlen(ret) == 0)) {
        free(ret);
        return (NULL);
      }
      b[0] = '\0';
      break;
    }
    b[read_ret] = '\0';
  }
  return (ret);
}

int main(void) {
  int fd;
  char *line;

  fd = open("file.txt", O_RDONLY);
  while ((line = get_next_line(fd)) != NULL) {
    printf("%s", line);
    free(line);
  }
  close(fd);
  return (0);
}
