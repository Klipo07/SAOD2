#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../lib/bstree.h"
#include "../lib/hashtab.h"
#include "../lib/header.h"


int main() {
  struct listnode *hashtab_KR[Hashtab_Size];
  struct listnode *hashtab_Add[Hashtab_Size];

  char words[MaxKeys][MaxKeyLenght];

  struct listnode *node_KR, *node_Add;
  double time_KR = 0.0, time_Add = 0.0;
  clock_t begin, end;

  FILE *file = fopen("parol.txt", "r");
  if (!file) {
    return 1;
  }

  for (int i = 0; fgets(words[i], MaxKeyLenght, file) && i < MaxKeys; i++) {
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);

  printf("#\t   KR\t\t Add \tcolizii_KR\t colizii_Add\n");
  hashtab_init(hashtab_KR);
  hashtab_init(hashtab_Add);

  for (int i = 0; i < MaxKeys; i++) {
    hashtab_add(hashtab_KR, words[i], i);
    hashtab_add_Add(hashtab_Add, words[i], i);
    if ((i + 1) % 10000 == 0) {
      char *word = words[0]; // words[getrand(0, i)];
      // bstree
      begin = clock();
      node_KR = hashtab_lookup(hashtab_KR, word);
      end = clock();
      time_KR = (double)(end - begin) / CLOCKS_PER_SEC;

      // hastab
      begin = clock();
      node_Add = hashtab_lookup_Add(hashtab_Add, word);
      end = clock();
      time_Add = (double)(end - begin) / CLOCKS_PER_SEC;

      printf("%d\t %f\t%f\t %d \t%d\n", i + 1, time_KR, time_Add, get_collisions(hashtab_KR), get_collisions(hashtab_Add));
    }
  }
  free_table(hashtab_KR);
  free_table(hashtab_Add);
  return 0;
}