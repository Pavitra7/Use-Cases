/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#define MY_STACK_SIZE 500
#define MY_PRIORITY 5
#define LENGTH 512
#define CACHE_SIZE 4 * 16 * 64

// The attacking flush function

void flush_cache() 
{
    unsigned char* cache = (unsigned char*)malloc(CACHE_SIZE);
    //if (cache == NULL) {
        // Error handling if memory allocation fails
      //  return;
    //}

   for (int j =0; j<LENGTH; j++)
   { // Write a pattern to each byte of memory
    for (int i = 0; i < CACHE_SIZE; i++) 
    {
        cache[i] = i % 256; 
        //printf("Trying to flush cache"); 
    }
    int32_t us;
    us=rand() % 2000;
    int32_t k_usleep(us);
}
}

//Thread of attacker that does the attack operation
K_THREAD_DEFINE(attack_thread, MY_STACK_SIZE,
                flush_cache, NULL,
                MY_PRIORITY, 0, 0);
                

