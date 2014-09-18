/*
Coursera HW/SW Interface
Lab 4 - Mystery Caches

Mystery Cache Geometries (for you to keep notes):
mystery0:
    block size =
    cache size =
    associativity =
mystery1:
    block size =
    cache size =
    associativity =
mystery2:
    block size =
    cache size =
    associativity =
mystery3:
    block size =
    cache size =
    associativity =
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real"
 * memory addresses. You can use any convenient integer value as a
 * memory address, you should not be able to cause a segmentation
 * fault by providing a memory address out of your programs address
 * space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  int block_size;

  for (block_size = 2;; block_size *= 2) {
    access_cache(0);

    if (access_cache(block_size - 1) == FALSE)
      break;

    flush_cache();
  }

  flush_cache();
  return block_size / 2;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int size) {
  int blocks;
  int i;

  for (blocks = 2;; blocks *= 2) {
    for (i = 0; i < blocks; i++)
      access_cache(size * i);

    if (access_cache(0) == FALSE)
      break;

    flush_cache();
  }

  flush_cache();
  return blocks / 2 * size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  int assoc;
  int i;

  for (assoc = 1;; assoc++) {
    access_cache(0);

    for (i = 0; i < assoc; i++)
      access_cache(size * i);

    if (access_cache(0) == FALSE)
      break;

    flush_cache();
  }

  flush_cache();
  return assoc - 1;
}

//// DO NOT CHANGE ANYTHING BELOW THIS POINT
int main(void) {
  int size;
  int assoc;
  int block_size;

  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.  You can
     test your geometry paramter discovery routines by calling
     cache_init() w/ your own size and block size values. */
  cache_init(0,0);

  block_size=get_block_size();
  size=get_cache_size(block_size);
  assoc=get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
