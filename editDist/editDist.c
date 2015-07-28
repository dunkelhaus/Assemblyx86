#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int editDist(char* word1, char* word2);
int min(int a, int b);
void swap(int** a, int** b);

int min(int a, int b){
  return a < b ? a:b;
}

void swap(int** a, int** b){
  int* temp = *a;
  *a = *b;
  *b = temp;
}

int editDist(char* word1, char* word2){

  int word1_len = strlen(word1);
  int word2_len = strlen(word2);
  int* oldDist = (int*)malloc((word2_len + 1) * sizeof(int));
  int* curDist = (int*)malloc((word2_len + 1) * sizeof(int));

  int i,j,dist;

  //intialize distances to length of the substrings
  for(i = 0; i < word2_len + 1; i++){
    oldDist[i] = i;
    curDist[i] = i;
    // printf("oldDist(1st for loop): %d\n", oldDist[i]);
    // printf("oldDist(1st for loop): %d\n", curDist[i]);
  }

  for(i = 1; i < word1_len + 1; i++)
  {
    curDist[0] = i;
    printf("curDist[0] outer: %d\n", curDist[0]);
    for(j = 1; j < word2_len + 1; j++){
      if(word1[i-1] == word2[j-1]){
        printf("J (ifloop): %d\n", j);
        printf("curDist[j] if loop: %d\n", curDist[j]);
        curDist[j] = oldDist[j - 1];
        printf("curDist[j] after assignment (if loop): %d\n", curDist[j]);
      }//the characters in the words are the same
      else{
        printf("J (elseloop): %d\n", j);
        curDist[j] = min(min(oldDist[j], //deletion
                          curDist[j-1]), //insertion
                          oldDist[j-1]) + 1; //substitution
        printf("curDist[j] (end of else): %d\n", curDist[j]);
      }
    }//for each character in the second word
    swap(&oldDist, &curDist);
  }//for each character in the first word
  for (i = 0; i < word2_len + 1; i++)
  {
    printf("Ending elements oldDist[]:                      %d\n", oldDist[i]);
    printf("Ending elements curDist[]: %d\n", curDist[i]);
  }
  dist = oldDist[word2_len];//using oldDist instead of curDist because of the last swap
  free(oldDist);
  free(curDist);
  return dist;

}

int main(int argc, char** argv){
  if(argc < 3){
    printf("Usage: %s word1 word 2\n", argv[0]);
    exit(1);
  }
  printf("The distance between %s and %s is %d.\n", argv[1], argv[2], editDist(argv[1], argv[2]));

  return 0;
}
