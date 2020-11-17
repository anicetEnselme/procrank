#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

int main()
{
   pid_t i=2;
   size_t j = 2666;
   char *texte = "/home/enselme/Documents/projects/procrank/procrank.py %d %d ";
   char buf[64];

   snprintf(buf, 64, texte,i,j);
   printf("%s\n", buf);

   system(buf);
   // for (i = 0; i < 100; i++) {
   //    snprintf(buf, 12, "pre_%d_suff", i); // puts string into buffer
   //    printf("%s\n", buf); // outputs so you can see it
   // }
}