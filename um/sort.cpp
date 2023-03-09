#include "sort.hpp"

void troca(Item *xp, Item *yp) {  
    Item temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  

void bubbleSort(Item arr[], double n, int *comparacoes) {
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Ultimos i elementos ja estao em seu lugar
    for (j = 0; j < n-i-1; j++) {
        if (arr[j].nota > arr[j+1].nota){
            troca(&arr[j], &arr[j+1]);
        }
        (*comparacoes)++;
    }
}