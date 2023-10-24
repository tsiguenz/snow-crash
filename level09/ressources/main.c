#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int ac, char **av) {
  if (ac != 2)
    return EXIT_FAILURE;
  char *filename = av[1];
  char str[100] = {0};
  int fd = open(filename, O_RDONLY);

  ssize_t len = read(fd, str, 50);
  for (ssize_t i = len - 1; i; i--) {
    str[i] = str[i] - i;
  }
  printf("%s\n", str);
  return EXIT_SUCCESS;
}
