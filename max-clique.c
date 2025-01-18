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


void generateCombinations(bool graph[MAX_VERTICES][MAX_VERTICES],
 int n, signed char *clique, signed char k,
   signed char *maxSize, signed char *maxClique) {

    for (signed char i = 0; i < k; i++) {
        clique[i] = i;
    }
    while (1) {
        // Print the current combination
        if (isClique(graph, clique, k)) {
            if (k > *maxSize) {
                *maxSize = k;
                for (signed char i = 0; i < k; i++) {
                    maxClique[i] = clique[i];
                }
            } 
            return;
        }
        
        // Find the rightmost element that can be incremented
        signed char i;
        for (i = k - 1; i >= 0; i--) {
            if (clique[i] < n - (k - 1) + i) {
                break;
            }
        }

        // If no element can be incremented, we're done
        if (i < 0) {
            break;
        }

        // Increment this element and update the subsequent elements
        clique[i]++; 
   
        for (signed char j = i + 1; j < k; j++) {
            clique[j] = clique[j - 1] + 1;
        }

    }
}



//todo:
//make it loop rolling
void initGraph(int graph[MAX_VERTICES][MAX_VERTICES],bool optGraph[MAX_VERTICES][MAX_VERTICES],signed char n){
    for (signed char row = 0; row < n; row++) {
        for (signed char colm = row+1; colm < n; colm++) { 
            optGraph[row][colm] = graph[row][colm] | graph[colm][row];
        }
    }
}

void initDeg(int graph[MAX_VERTICES][MAX_VERTICES],signed char* deg,int n){
    for(signed char i =0;i<n;i++){
        for(signed char j =0;j<n;j++){
        deg[i]+=graph[i][j];
        }
    }
}



void findMaxClique(int graph[MAX_VERTICES][MAX_VERTICES], int n) {
    signed char clique[n];
    signed char maxClique[n];
    signed char maxSize = 0;
    signed char deg[n];
    initDeg(graph,deg,n);
    bool optGraph [MAX_VERTICES][MAX_VERTICES];
    initGraph(graph,optGraph,n);
    unsigned char i = 0;
    unsigned char j = n;
    while (i + 1 < j) { 
        unsigned char k = (i + j) >> 1; 
        maxSize = 0;
        generateCombinations(optGraph, n, clique, k, &maxSize, maxClique);
        if (maxSize > 0) {
            i = k; 
        } else {
            j = k;
        }
    }

    printf("Clique Members: ");
    printSolution(maxClique, maxSize);
    printf("Size: %d\n", maxSize);

}
