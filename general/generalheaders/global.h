#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/stat.h>
#include <string.h>
#include <math.h>

#define EPSILON  0.001
#define POISON 0xDEAD
#define NUMSTEP 10
#define FICT_ELEM 0
#define NOT_FOUND -1
#define REASONSTRSIZE 80
#define ORDERSIZE 300
#define DATASIZE 50
#define STRSIZE 30
#define _VAR_STR_SIZE_ 50
#define _RAMSTART_   100
#define _STACK_SIZE_ 50

#define DEBUG

#endif

#ifdef DEBUG
    #define ONDEBUG(func) func
#else
    #define ONDEBUG(func) 
#endif