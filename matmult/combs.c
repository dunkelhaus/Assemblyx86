#include <stdio.h>
#include <stdlib.h>


void print_mat(int** mat, int num_rows, int num_cols);
void free_mat(int** mat, int num_rows, int num_cols);
int max(int a, int b);
int min(int a, int b);
int num_combs(int n, int k);

void combinationComputer (int* temp, int arr[], int data[], int start, int end, int index, int k, int *x, int *y, int count); // Have to translate this function into X86 assembly
int** get_combs(int* items, int k, int len); // Have to translate this function into X86 assembly

int max(int a, int b){
  return a > b ? a : b;
}

int min(int a, int b){
  return a < b ? a : b;
}

int num_combs(int n, int k){
  int combs = 1;
  int i;
  
  for(i = n; i > max(k, n-k); i--){
    combs *= i;
  }

  for(i = 2; i <= min(k, n - k); i++){
    combs /= i;
  }
  
  return combs;

}

void print_mat(int** mat, int num_rows, int num_cols){
  int i,j;
  
  for(i = 0; i < num_rows; i++){
    for( j = 0; j < num_cols; j++){
      printf("%d ", mat[i][j]); 
    }
    printf("\n");
  }
}

void free_mat(int** mat, int num_rows, int num_cols){
  int i;
  
  for(i = 0; i < num_rows; i++){
    free(mat[i]);
  }
  free(mat);
}

int** get_combs(int* items, int k, int len)
{
  int* data; // 1D array that stores 1 combination at a time and transfers it to temp
  int* temp; // 1D array that stores all combinations as a single chunk
  int** result; // Final 2D array that stores each combination as a row 
  int i;
  int x = 0;
  int y = k;
  int count = 0;
  int j = 0;

  result = (int**)malloc(num_combs(len, k) * sizeof(int*));

  for (i = 0; i < num_combs(len, k); i++)
    result[i] = (int*)malloc(k * sizeof(int));

  data = (int*)malloc(k * sizeof(int));
  temp = (int*)malloc((num_combs(len, k) * k) * sizeof(int));

  combinationComputer(temp, items, data, 0, len - 1, 0, k, &x, &y, count); // recursive function
  x = 0;
  count = 0;
  y = k;
   
  //Now, we transfer all the combinations present in the 1D temp array into the 2D result, which takes each combination as a row.

  for (x = 0; x < num_combs(len, k); x++) 
  {
    for (i = count; i < y; i++) 
    {
      result[x][j] = temp[i];
      j++;  
      
      if (j == k)
        j = 0;
    }
    
    count = count + k;
    y = y + k; 
  }
  
  free(data);
  free(temp);
  
  return result;
  
}

void combinationComputer (int* temp, int* arr, int* data, int start, int end, int index, int k, int *x, int *y, int count)
{
  int i;

  if (index == k)
  {
    if (count > k)
    {
      *x = *x + k;
      *y = *y + k;
    }

    for (i = *x; i < *y; i++)
      temp[i] = data[i - *x]; // storing all combinations into temp[] as a single chunk, one combination at a time

    return;

  }

  for (i = start; i <= end && end - i + 1 >= k - index; i++)
  {
    data[index] = arr[i]; // each combination is stored in data[], with each subsequent combination overwriting the previous one. 
    count = count + 1;
    combinationComputer(temp, arr, data, i + 1, end, index + 1, k, x, y, count); // recursive call

  }

}

int main(){
  int num_items;
  int* items; 
  int i,k;
  int** combs;
  printf("How many items do you have: ");
  scanf("%d", &num_items);
  
  items = (int*) malloc(num_items * sizeof(int));
  
  printf("Enter your items: ");
  for(i = 0; i < num_items; i++){
    scanf("%d", &items[i]);
  } 
  
  printf("Enter k: ");
  scanf("%d", &k);
  
  combs = get_combs(items, k, num_items);
  print_mat(combs,num_combs(num_items, k) ,k);
  free(items);
  free_mat(combs,num_combs(num_items, k), k);
  
  return 0;
}

