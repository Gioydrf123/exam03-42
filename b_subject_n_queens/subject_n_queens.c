#include <stdio.h>
#include <stdlib.h>

void print_solution(int *queens, int n) {
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      fprintf(stdout, " ");
    }
    fprintf(stdout, "%d", queens[i]);
  }
  fprintf(stdout, "\n");
}

int is_safe(int *queens, int col, int row) {
  for (int i = 0; i < col; i++) {
    if (queens[i] == row || abs(queens[i] - row) == abs(i - col)) {
      return 0;
    }
  }
  return 1;
}

void solve(int *queens, int col, int n) {
  if (col == n) {
    print_solution(queens, n);
    return;
  }
  for (int row = 0; row < n; row++) {
    if (is_safe(queens, col, row)) {
      queens[col] = row;
      solve(queens, col + 1, n);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return 1;
  }
  int n = atoi(argv[1]);
  if (n < 0) {
    return 1;
  }
  int *queens = malloc(n * sizeof(int));
  if (!queens) {
    return 1;
  }
  solve(queens, 0, n);
  free(queens);
  return 0;
}
