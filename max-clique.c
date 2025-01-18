#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void printSolution(signed char vertices[], signed char size) {
    for (signed char i = 0; i < size; i++) {
        printf("%d ", vertices[i]);
    }
    printf("\n");
}

bool isClique(bool graph[MAX_VERTICES][MAX_VERTICES], signed char clique[], signed char size) {
    for (signed char i = 0; i < size; i++) {
        signed char curi = clique[i];
        for (signed char j = i+1; j < size; j++) {
            signed char curj=clique[j];
            if (!(graph[curi][curj])) {
                return false;
            }
        }
    }
    return true;
}

// void generateCombinations( bool graph[MAX_VERTICES][MAX_VERTICES], 
// signed char n, signed char *clique, signed char k, signed char start,
//  signed char currentSize, signed char *maxSize, signed char *maxClique,bool *flag,signed char deg[]) {
//          if (currentSize == k) {
//         if (isClique(graph, clique, k)) {
//             if (k > *maxSize) {
//                 *maxSize = k;
//                 for (int i = 0; i < k; i++) {
//                     maxClique[i] = clique[i];
//                 }
//             }
//         }
//         return;
//     }

//     for (int i = start; i < n; i++) {
//         clique[currentSize] = i;
//         generateCombinations(graph, n, clique, k, i + 1, currentSize + 1, maxSize, maxClique,flag,deg);
//     }
// }


void generateCombinations( bool graph[MAX_VERTICES][MAX_VERTICES], 
signed char n, signed char *clique, signed char k, signed char start,
 signed char currentSize, signed char *maxSize, signed char *maxClique,bool *flag,signed char deg[]) {
    printf("testing {");
    for(int i = 0; i < currentSize; i++){
        printf("%d ",clique[i]);
    }
    printf("}\n");
    if(*flag)return;
    if (currentSize == k) {
        if (isClique(graph, clique, k)) {
            printf("find!!\n");
            *flag=true;
            if (k > *maxSize) {
                *maxSize = k;
                for (int i = 0; i < k; i++) {
                    maxClique[i] = clique[i];
                }
            }
        }
        return;
    }

    for (int i = start; i < n; i++) {

        if(deg[i]>=k-1){
        printf("deg %d is %d while k is %d \n",i,deg[i],k);
        clique[currentSize] = i;
        printf("Calling\n");
        generateCombinations(graph, n, clique, k, i + 1, currentSize + 1, maxSize, maxClique, flag,deg);
        }
        if(*flag)return;
      }
}




// void generateCombinations(bool graph[MAX_VERTICES][MAX_VERTICES],
//  int n, signed char *clique, signed char k,
//    signed char *maxSize, signed char *maxClique) {

//     for (signed char i = 0; i < k; i++) {
//         clique[i] = i;
//     }
//     while (1) {
//         // Print the current combination
//         if (isClique(graph, clique, k)) {
//             if (k > *maxSize) {
//                 *maxSize = k;
//                 for (signed char i = 0; i < k; i++) {
//                     maxClique[i] = clique[i];
//                 }
//             } 
//             return;
//         }
        
//         // Find the rightmost element that can be incremented
//         signed char i;
//         for (i = k - 1; i >= 0; i--) {
//             if (clique[i] < n - (k - 1) + i) {
//                 break;
//             }
//         }

//         // If no element can be incremented, we're done
//         if (i < 0) {
//             break;
//         }

//         // Increment this element and update the subsequent elements
//         clique[i]++; 
   
//         for (signed char j = i + 1; j < k; j++) {
//             clique[j] = clique[j - 1] + 1;
//         }

//     }
// }



//todo:
//make it loop rolling
void initGraph(int graph[MAX_VERTICES][MAX_VERTICES],bool optGraph[MAX_VERTICES][MAX_VERTICES],signed char n,signed char deg[]){
    for (signed char row = 0; row < n; row++) {
        for (signed char colm = row+1; colm < n; colm++) { 
            bool t = graph[row][colm] | graph[colm][row];
            if(t){
                optGraph[row][colm] = t;
                deg[row] +=t;
                deg[colm]+=t;
            }
        }
    }
}

void findMaxClique(int graph[MAX_VERTICES][MAX_VERTICES], int n) {
    signed char clique[n];
    signed char maxClique[n];
    signed char maxSize = 0;
    signed char deg[n];
    for (int i =0;i<n;i++)deg[i]=0;
    bool optGraph [MAX_VERTICES][MAX_VERTICES];
    initGraph(graph,optGraph,n,deg);

int left = 0, right = n;
 while (left <= right) {
    bool flag=false;
        int k = left + (right - left) / 2;
        generateCombinations(optGraph, n, clique, k, 0, 0, &maxSize, maxClique,&flag,deg);
     
        if (flag) {
            left = k + 1; // Move the left pointer to find the last true
        } else {
            right = k - 1; // Move the right pointer to search in the left half
        }
    }

    printf("Clique Members: ");
    printSolution(maxClique, maxSize);
    printf("Size: %d\n", maxSize);

}
