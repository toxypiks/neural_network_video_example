#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define OLIVEC_IMPLEMENTATION
#include "olive.c"

#define READ_END 0
#define WRITE_END 1

#define WIDTH 800
#define HEIGHT 600
uint32_t pixels[WIDTH*HEIGHT];

int main (void)
{
  int pipefd[2];

  if (pipe(pipefd) < 0) {
    fprintf(stderr, "ERROR: could not create pipe: %s\n", strerror(errno));
    return 1;
  }

  pid_t child = fork();
  if (child < 0) {
    fprintf(stderr, "ERROR: could not fork a child: %s\n", strerror(errno));
    return 1;
  }
  if (child == 0) {
    // replace standard input of ffmpeg with the read end of the pipe (pipefd[0])
    // dup2(pipefd[READ_END], STDIN_FILENO);
    if (dup2(pipefd[READ_END], STDIN_FILENO) < 0) {
      fprintf(stderr, "ERROR: could not reopen read end of pipe as stdin: %s\n", strerror(errno));
      return 1;
    }
    close(pipefd[WRITE_END]);
    int ret = execlp("ffmpeg",
                     "ffmpeg",
                     "-loglevel", "verbose",
                     "-y",
                     "-f", "rawvideo",
                     "-pix_fmt", "rgba",
                     "-s", "800x600",
                     "-r", "60",
                     "-an",
                     "-i", "-",
                     "-c:v", "libx264",

                     "../output/output.mp4",
                     NULL
      );
    if (ret < 0) {
      fprintf(stderr, "ERROR: could not run ffmpeg as a child process: %s\n", strerror(errno));
      return 1;
    }
    assert(0 && "unreachable");
  }
  close(pipefd[READ_END]);

  Olivec_Canvas oc = olivec_canvas(pixels, WIDTH, HEIGHT, WIDTH);
  olivec_fill(oc, 0xFF181818);
  olivec_circle(oc, WIDTH/2, HEIGHT/2, HEIGHT/4, 0xFF0000FF);

  for (size_t i = 0; i < 60; ++i) {
    write(pipefd[WRITE_END], pixels, sizeof(*pixels)*WIDTH*HEIGHT);
  }
  close(pipefd[WRITE_END]);

  //waiting for child being finished with execution
  wait(NULL);
  printf("Done rendering the video\n");
  return 0;
}
