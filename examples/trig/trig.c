/* trig - Trigonometric functions.

   Copyright (c) 2011 Universidad Rey Juan Carlos
   
   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   
   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.
   
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <CL/opencl.h>

#define N 8

extern int exec_trig_kernel (const char *program_source, 
                             int n, void *srcA, void *dst);

int
main (void)
{
  FILE *source_file;
  char *source;
  int source_size;
  cl_float4 *srcA;
  cl_float4 *dst;
  int i;

  source_file = fopen (SRCDIR "/trig.cl", "r");
  fseek (source_file, 0, SEEK_END);
  source_size = ftell (source_file);
  fseek (source_file, 0, SEEK_SET);

  source = (char *) malloc (source_size+1);
  assert (source != NULL);

  fread (source, source_size, 1, source_file);
  source[source_size] = '\0';

  fclose (source_file);

  srcA = (cl_float4 *) malloc (N * sizeof (cl_float4));
  dst = (cl_float4 *) malloc (N * sizeof (cl_float4));

  for (i = 0; i < N; ++i)
    {
      srcA[i].s0 = i;
      srcA[i].s1 = i;
      srcA[i].s2 = i;
      srcA[i].s3 = i;
    }

  exec_trig_kernel (source, N, srcA, dst);

  for (i = 0; i < N; ++i)
    {
      printf ("f(%f, %f, %f, %f) = (%f, %f, %f, %f)\n",
	      srcA[i].s0, srcA[i].s1, srcA[i].s2, srcA[i].s3,
	      dst[i].s0, dst[i].s1, dst[i].s2, dst[i].s3);
    }

  printf ("OK\n");
  return 0;
}
