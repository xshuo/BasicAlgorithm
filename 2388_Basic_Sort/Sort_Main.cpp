//POJ2388
#include <cstdlib>
#include <iostream>
#include <cstdio>

//#include <memory.h>
#include <math.h>
#include <string.h>

using namespace std;

int g_input_length;
//int g_array[10000];
int* g_array;
//extern void insertion_sort(int* array, int start, int end);
//extern void merge_sort(int* array, int start, int end);
//extern void q_sort(int* array, int start, int end);
//extern void radix_sort(int* array, int start, int end);

extern int find_k_num(int* array, int start, int end, int k);

int main(int argc, char *argv[])
{
    //freopen("E:\\Workplace\\POJ\\input.txt", "r", stdin); 
    scanf("%d", &g_input_length);
    g_array = (int*)malloc(g_input_length * sizeof(int));
    for (int i = 0; i < g_input_length; ++i) {
        scanf("%d", g_array + i);
    }
    
    //radix_sort(g_array, 0, g_input_length);
    //merge_sort(g_array, 0, g_input_length);
    //q_sort(g_array, 0, g_input_length);
    
    printf("%d", find_k_num(g_array, 0, g_input_length, (g_input_length - 1) / 2));
    
    printf("\n");
    for (int i = 0; i < g_input_length; ++i){
        printf("%d\n", g_array[i]);         
    }
    return EXIT_SUCCESS;
}