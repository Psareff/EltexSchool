#include <stdio.h>
#include <stdlib.h>

// RUN ./largest 2 4 5 8 3 10 7 1
int FindLargest(int arr[], int length) 
{
    int temp = arr[0];
    for (int i = 1; i < length; i++)
    {
        if (arr[i] > temp)
            temp = arr[i];
    }
    return temp;
}

int main(int argc, char** argv)
{
    int arr[argc];
    for (int i = 1; i < argc; i++)
        arr[i] = atoi(argv[i]);
    printf ("Largest: %d\n", FindLargest(arr, argc));
}