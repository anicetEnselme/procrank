#define _GNU_SOURCE

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

static void* (*real_malloc)(size_t)=NULL;

static void sandbox_init(void)
{
  real_malloc = dlsym(RTLD_NEXT, "malloc");
  if (NULL == real_malloc) {
    fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
  }
  system("echo boss > 2");
  printf("Init ok\n");
}

void *malloc(size_t size)
{
  if(real_malloc==NULL) {
    sandbox_init();
  }
 // int argvsize = 5;
  //char **argvs = malloc(argvsize * sizeof(*argvs));
  //char *newenv[] = { NULL };
  //argvs[0] = PYTHON;
  //argvs[argvsize - 1] = NULL;  
  //memcpy(&argvs[1], )
  char *command = "/home/enselme/Documents/projects/procrank/procrank.py %d %d >text.txt";
  char buf[64];
  void *p = NULL;
  pid_t pid = getpid();
  snprintf(buf, 64, command, pid, size);
  fprintf(stderr, "process (%d) asked for %ld bytes memory\n", pid, size);
  fprintf(stderr, "Command to execute: (%d)\n", system(command));
  system(command);
   
  p = real_malloc(size);
  return p;
}


