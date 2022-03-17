#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>


#ifndef _FTRACE_UTIL_IMPL_
#define _FTRACE_UTIL_IMPL_



int setup_tracer();

void disable_tracing();

void clear_trace();




#endif