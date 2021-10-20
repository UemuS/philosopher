#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

int main()
{
	struct timeval current_time;
  	gettimeofday(&current_time, NULL);
	printf("time is %ld\n", current_time.tv_sec);
}