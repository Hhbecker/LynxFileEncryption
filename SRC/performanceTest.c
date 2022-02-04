/*
This file contains code developed by R. Bryant and D. O'Hallaron at 
Carnegie Mellon University. The code is used to obtain precise 
performance information from a given C function. 
*/


#include <sys/time.h>
#include <sys/resource.h>

/* Below are statements to set up the performance measurement utilities */
/* we use rdtsc, clock, and getusage utilities to measure performance */

//#define rdtscll(val) __asm__ __volatile__("rdtsc" : "=A" (val))
static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

/* the getUserTime function is used for measurement */

static long int getUserTime()
{
	int who= RUSAGE_SELF;
	int ret;
	struct rusage usage;
	struct rusage *p=&usage;
	//long int current_time;

	ret=getrusage(who,p);
	if(ret == -1)
	{
		printf("Could not get GETRUSAGE to work in function %s at line %d in file %s\n",
				__PRETTY_FUNCTION__, __LINE__, __FILE__);
		exit(1);
	}
	return (p->ru_utime.tv_sec * 1000000 + p->ru_utime.tv_usec);
}

/* end of definitions to set up measurement utilities */

// Code below belongs inside function of interest

    ///////////////////////////////////
	/* the variables below are used for performance measurement */
	long int rusage_start_time = 0;
    long int rusage_end_time = 0;
    unsigned long long rdtsc_start_time = 0;
    unsigned long long rdtsc_end_time = 0;

	/* call system functions to start measuring performance */
    rusage_start_time = getUserTime();
	rdtsc_start_time = rdtsc();
    ///////////////////////////////////

    /* the remaining lines in this function stop the measurement and set the values before returning */
	rusage_end_time = getUserTime();
    rdtsc_end_time = rdtsc();

	rusage_end_time = rusage_end_time - rusage_start_time;
	rdtsc_end_time = rdtsc_end_time - rdtsc_start_time;

    printf("\nrusage time = %ld\n", rusage_end_time);
    printf("\nrdtsc time = %llu\n\n", rdtsc_end_time);

