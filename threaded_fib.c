#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 1

typedef void (*function) (float *, int *);

struct thread_data
{
  int thread_id;
  function target_fn;
  int n;
  float * a;
};

struct thread_data thread_data_array[NUM_THREADS];

/* thread function */
static void * run_fib (void * thread_arg)
{
  struct thread_data * data = (struct thread_data *)thread_arg;
  printf ("From thread id: %ld\n", (unsigned long)pthread_self ());
  data->target_fn (data->a, &data->n);
  pthread_exit (NULL);
}

void threaded_fib (float * a, int n, function fp)
{
  pthread_t threads[NUM_THREADS];
  pthread_attr_t attr;
  int rc;
  void * status;

  printf ("From thread id: %ld\n", (unsigned long)pthread_self ());
  thread_data_array[0].thread_id = 0;
  thread_data_array[0].target_fn = fp;
  thread_data_array[0].a = a;
  thread_data_array[0].n = n;
  pthread_attr_init (&attr);
  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
  rc = pthread_create (&threads[0], &attr, run_fib, &thread_data_array[0]);
  if (rc)
    {
      printf ("ERROR: return code from pthread_create ()is %d\n", rc);
      exit (-1);
    }
  pthread_attr_destroy (&attr);
  rc = pthread_join (threads[0], &status);
  if (rc)
    {
      printf ("ERROR: return code from pthread_join ()is %d\n", rc);
      exit (-1);
    }
  printf ("main: Completed join with thread 0 havng status %ld\n", (long)status);
}
