#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <unistd.h>

int main (void)
{
  pid_t child = fork();
  if (child < 0) {
    fprintf(stderr, "ERROR: could not fork a child: %s\n", strerror(errno));
    return 1;
  }
  if (child == 0) {
    printf("Hello from child\n");
    return 0;
  }
  printf("Hello from parent. The childs pid is %d\n", child
    );

  return 0;
}
