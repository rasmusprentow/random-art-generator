#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <time.h>

#include <sys/time.h>

#include "walker.h"


void seed()
{
    struct timeval  tp;

    gettimeofday(&tp ,NULL);

    srand( ( tp.tv_sec  * tp.tv_usec));

}
