#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str) {
  int len = 0;
  while (str[len])
    len++;
  return len;
}

void ft_putstr(char *str) {
  int i = 0;
  while (str[i]) {
    write(1, &str[i], 1);
    i++;
  }
  write(1, "\n", 1);
}

void swap(char *a, char *b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

int should_swap(char *str, int start, int current) {
  int i = start;
  while (i < current) {
    if (str[i] == str[current])
      return 0;
    i++;
  }
  return 1;
}

void generate_permutations(char *str, int start, int end, char **result,
                           int *count) {
  if (start == end) {
    result[*count] = (char *)malloc((end + 2) * sizeof(char));
    int i = 0;
    while (i <= end) {
      result[*count][i] = str[i];
      i++;
    }
    result[*count][i] = '\0';
    (*count)++;
    return;
  }

  int i = start;
  while (i <= end) {
    if (should_swap(str, start, i)) {
      swap(&str[start], &str[i]);
      generate_permutations(str, start + 1, end, result, count);
      swap(&str[start], &str[i]);
    }
    i++;
  }
}

int count_permutations(int n) {
  int count = 1;
  int i = 1;
  while (i <= n) {
    count *= i;
    i++;
  }
  return count;
}

int compare_strings(char *a, char *b) {
  int i = 0;
  while (a[i] && b[i] && a[i] == b[i])
    i++;
  return a[i] - b[i];
}

void sort_permutations(char **permutations, int count) {
  int i = 0;
  while (i < count - 1) {
    int j = 0;
    while (j < count - i - 1) {
      if (compare_strings(permutations[j], permutations[j + 1]) > 0) {
        char *temp = permutations[j];
        permutations[j] = permutations[j + 1];
        permutations[j + 1] = temp;
      }
      j++;
    }
    i++;
  }
}

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;

  char *str = argv[1];
  int len = ft_strlen(str);

  if (len == 0)
    return 1;

  int total_permutations = count_permutations(len);
  char **permutations = (char **)malloc(total_permutations * sizeof(char *));
  int count = 0;

  generate_permutations(str, 0, len - 1, permutations, &count);
  sort_permutations(permutations, count);

  int i = 0;
  while (i < count) {
    ft_putstr(permutations[i]);
    free(permutations[i]);
    i++;
  }
  free(permutations);

  return 0;
}