#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void printSolution(signed char vertices[], signed char size) {
    signed char gap =size%4;
    for (signed char i = 0; i < size%4; i++){
        printf("%d ", vertices[i]);
    }
    for (signed char i = gap; i < size; i+=4) {
        printf("%d ", vertices[i]);
        printf("%d ", vertices[i+1]);
        printf("%d ", vertices[i+2]);
        printf("%d ", vertices[i+3]);
    }
    printf("\n");
}

bool isClique(bool graph[MAX_VERTICES][MAX_VERTICES], signed char clique[], signed char size) {
        signed char curi = clique[size-1];
        for (signed char j = 0; j < size-1; j++) {
            signed char curj=clique[j];
            if (!(graph[curi][curj])) {
                return false;
            }
    }
    return true;
}


bool generateCombinations( bool graph[MAX_VERTICES][MAX_VERTICES], 
signed char n, signed char *clique, signed char k, signed char start,
 signed char currentSize, signed char *maxSize, signed char *maxClique,signed char deg[]) {
        if (!isClique(graph, clique, currentSize)) {
            return false;
        }
        
    if (currentSize == k) {
            if (k > *maxSize) {
                *maxSize = k;
                for (int i = 0; i < k; i++) {
                    maxClique[i] = clique[i];
                }
            }
            return true;
        }
    
    signed char t = k-2;
    signed char t2 = currentSize+n;
    for (int i = start; i < n; i++) {
        if(k>t2-i)return false;
        if(deg[i]>t){
        clique[currentSize] = i;
        if(generateCombinations(graph, n, clique, k, i + 1, currentSize + 1, maxSize, maxClique,deg))
        return true;
        }
      }
      return false;
}


//todo:
//make it loop rolling
void initGraph(int graph[MAX_VERTICES][MAX_VERTICES],bool optGraph[MAX_VERTICES][MAX_VERTICES],signed char n,signed char deg[]){
    for (signed char row = 1; row < n; row++) {
        for (signed char colm = 0; colm < row; colm++) { 
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
    signed char size = n * sizeof(signed char);
    signed char *clique = (signed char *)malloc(size);
    signed char *maxClique = (signed char *)malloc(size);
    signed char *deg = (signed char *)calloc(n, sizeof(signed char));
    signed char maxSize = 0;
    bool optGraph [MAX_VERTICES][MAX_VERTICES];
    initGraph(graph,optGraph,n,deg);
    
int left = 0, right = n;
 while (left <= right) {
        int k = left + ((right - left) >>1);
        bool flag = generateCombinations(optGraph, n, clique, k, 0, 0, &maxSize, maxClique,deg);
        if (flag) {
            left = k + 1; 
        } else {
            right = k - 1; 
        }
    }

    printf("Clique Members: ");
    printSolution(maxClique, maxSize);
    printf("Size: %d\n", maxSize);
free(clique);
free(maxClique);
free(deg);
}
