#include  <errno.h>
#include  <stdlib.h>
#include  <pthread.h>
#include  <stdio.h>
#include  <string.h>
#include  <unistd.h>

#define FALSE 0
#define TRUE  1
#define SBUFSIZE        16

struct SharedData {
  int         isopen;
  unsigned int    front;
  unsigned int    count;
  unsigned int    bufsize;
  char            buf[SBUFSIZE];
  pthread_mutex_t mutex;
  pthread_cond_t  notEmpty;
  pthread_cond_t  notFull;
};

void
initialize( struct SharedData * sptr )    // Looks like a ctor
{
  sptr->isopen = TRUE;
  sptr->front = 0;
  sptr->count = 0;
  sptr->bufsize = SBUFSIZE;
  pthread_mutex_init( &sptr->mutex, 0 );
  pthread_cond_init( &sptr->notFull, 0 );
  pthread_cond_init( &sptr->notEmpty, 0 );
}

void *
consumer( void * arg )
{
  struct SharedData * d = (struct SharedData *)arg;
  char      buffer[200];
  char *      p2;
  int     i;

  pthread_detach( pthread_self() );
  while ( d->isopen )
  {
    pthread_mutex_lock( &d->mutex );
    while ( d->count == 0 )
    {
      pthread_cond_signal( &d->notFull );
      printf( "BKR consumer() waits when shared buffer is empty.\n" );
      pthread_cond_wait( &d->notEmpty, &d->mutex );
    }
    sleep( 2 );   // pretend to do something
    printf( "BKR consumer() now takes %d bytes from buffer.\n", d->count );
    p2 = buffer;
    for ( i = 0 ; (d->count > 0) && (i < sizeof(buffer) ) ; i++ )
    {
      p2[i] = d->buf[d->front];
      d->front = (d->front + 1) % d->bufsize;
      --d->count;
    }
    printf( "%s\n", p2 );
    pthread_cond_signal( &d->notFull );
    pthread_mutex_unlock( &d->mutex );
  }
  return 0;
}

void *
producer( void * arg )
{
  struct SharedData * d = (struct SharedData *)arg;
  int     i;
  int     limit;
  int     back;
  char      p2[100];

  while ( scanf( " %[^\n]", p2 ) > 0 )
  {
    pthread_mutex_lock( &d->mutex );
    while ( d->count == d->bufsize )
    {
      pthread_cond_signal( &d->notEmpty );
      printf( "BKR producer() waits when shared buffer is full.\n" );
      pthread_cond_wait( &d->notFull, &d->mutex );
    }
    limit = strlen( p2 );
    for ( i = 0 ; i < limit ; i++ )
    {
      if ( d->count < d->bufsize )
      {
        back = (d->front + d->count) % d->bufsize;
        d->buf[back] = p2[i];
        ++d->count;
      }
      else
      {
        pthread_cond_signal( &d->notEmpty );
        printf( "BKR producer() waits when shared buffer is full.\n" );
        pthread_cond_wait( &d->notFull, &d->mutex );
      }
    }
    pthread_cond_signal( &d->notEmpty );
    pthread_mutex_unlock( &d->mutex );
  }
  d->isopen = 0;    // is this bad?
  return 0;
}

int
main( int argc, char ** argv )
{
  pthread_t   tid;
  char *      func = "main";
  struct SharedData * sharedData;

  if ( (sharedData = (struct SharedData *)malloc( sizeof(struct SharedData) )) == 0 )
  {
    printf( "malloc() failed in %s.\n", func );
    return 1;
  }
  else
  {
    initialize( sharedData );
    pthread_create( &tid, 0, consumer, sharedData );
    pthread_create( &tid, 0, producer, sharedData );
    pthread_exit( 0 );
  }
}
