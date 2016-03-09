/**
  Burak Aslan
  Homework 6
  CS3650
  Computer Systems
**/

#include <stdio.h>
#include <math.h>
#define MAX_NUM_ROWS 128
#define HIT 1
#define MISS 0

/**
  struct row - represents a cache line
  int valid - if it is valid or not
  int timeStamp - when it was last visited
**/
struct row {
  // timestamp when last visited
  int timeStamp;
  // tag of the row
  int tag;
  // Is it valid
  int valid;
};

// Cache struct
struct row cache[MAX_NUM_ROWS];

/**
  int findHitMiss - returns if the set/tag/index is a hit (1) or a miss (0)
  int setNum - current set we are on
  int tag - the tag of the cache row
  int index - the index of the cache set
**/
int findHitMiss(int setNum, int index, int tag) {

  int i = 0; // Counter
  int j = 0; // Row Index
  int currHit = 0; // If we hit or not

  for (j = (setNum*index); j < (setNum + (setNum*index)); j++)
    if (cache[j].tag == tag && cache[j].valid) {
      currHit = 1;
      return HIT;
    };

  for (j = (setNum*index); j < (setNum + (setNum*index)); j++)
    if (cache[j].valid) {
      i++;
    };

  for (j = (setNum*index); j < (setNum + (setNum*index)); j++)
    if (!cache[j].valid) {
      cache[j].valid = 1;
      cache[j].tag = tag;
      cache[j].timeStamp = i;
      currHit = 0;
      return MISS;
    };

  for (j = (setNum*index); j < (setNum + (setNum*index)); j++)
    cache[j].timeStamp = cache[j].timeStamp  - 1;

  for (j = (setNum*index); j < (setNum + (setNum*index)); j++)
      if (cache[j].timeStamp == -1) {
        cache[j].timeStamp = i - 1;
        cache[j].tag = tag;
        cache[j].valid = 1;
        currHit = 0;
        return MISS;
      };

  return MISS;
};


int main() {

  // Associativity of the cache
  int assoc;
  // How much the size of the cache is
  int cacheAlloc;
  // How much size of each block of cache
  int blockAlloc;
  // YOU CAN REPLACE THIS
  int inputArr[] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56,
    60, 64, 68, 72, 76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15,
  39, 11, 51, 57, 41 };

  printf("Cache Size?\n");
  scanf("%d", &cacheAlloc);
  printf("Block Size?\n");
  scanf("%d", &blockAlloc);
  printf("Associativity of the cache?\n");
  printf("Direct-Mapped = 1\n");
  printf("Fully Associative = %d\n", cacheAlloc / blockAlloc);
  scanf("%d", &assoc);

  // Number of sets in cache
  int numSets = (cacheAlloc/blockAlloc)/ assoc;

  // loop over all sets and rows
  for (int i = 0; i < sizeof(inputArr)/sizeof(inputArr[0]); i++) {
    int getTag = (inputArr[i]/blockAlloc)/numSets;
    int currIndex = (inputArr[i] / blockAlloc) % numSets;
    int hitOrMiss = findHitMiss(assoc, currIndex, getTag);
    hitOrMiss ? printf("%d: HIT \n", inputArr[i]) : printf("%d: MISS \n", inputArr[i]);
  };

  return 0;
};
