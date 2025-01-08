#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main (void)
{
  pid_t child = fork();
  if (child < 0) {
    fprintf(stderr, "ERROR: could not fork a child: %s\n", strerror(errno));
    return 1;
  }
  if (child == 0) {
    int ret = execlp("ffmpeg",
                     "ffmpeg",
                     //"-i", "-",
                     //"-f", "rawvideo",
                     NULL
      );
    if (ret < 0) {
      fprintf(stderr, "ERROR: could not run ffmpeg as a child process: %s\n", strerror(errno));
      return 1;
    }
    assert(0 && "unreachable");
  }
  //waiting for child being finished with execution
  wait(NULL);
  printf("Done rendering the video\n");
  return 0;
}
