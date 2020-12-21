/* 1. Vector */

/* Allowed Header */
#include <stdio.h>
#include <stdlib.h>

/* Given Function */
int empty(int *a);
void push(int **a, int *element_size, int *alloc_size, int value);
int pop(int **a, int *element_size, int *alloc_size);
int front(int *a, int element_size);
int back(int *a, int element_size);
int print_all(int *a, int element_size);

/* Code */
int main () {
    int element_size = 0;
    int alloc_size = 1;
    int* a;
    char cmd;
    int value;

    // Init Vector
    a = (int *) malloc (sizeof(int)*alloc_size);
    a[0] = element_size;

    while (1) {
        cmd = getchar();    // get command

        // Command 0 : isEmpty
        if (cmd == '0') {
            printf("%d\n", empty(a));
        }

        // Command 1 : Push
        else if (cmd == '1') {
            scanf(" %d", &value);
            push(&(a), &element_size, &alloc_size, value);
        }

        // Command 2 : Pop
        else if (cmd == '2') {
            pop(&(a), &element_size, &alloc_size);
        }

        // Command 3 : Front
        else if (cmd == '3') {
            front(a, element_size);
        }

        // Command 4 : Back
        else if (cmd == '4') {
            back(a, element_size);
        }

        // Command 5 : Print
        else if (cmd == '5') {
            // printf("Vector size : %d Element Size : %d\n", alloc_size, element_size); // for debugging
            print_all(a, element_size);
        }
        
        // Exception
        else if (cmd == EOF) {
            printf("Error : Meet EOF. Ending Program...\n");
            break;
        }

        // Exception
        else {
            printf("Error : Enter command (0~5)\n");
        }

        getchar(); // ENTER
    }

    return 0;
}

int empty(int *a) {
    // If element size = 0
    if (a[0] == 0) {
        return 1;
    }

    // If element size != 0
    else {
        return 0;
    }
}

void push(int **a, int *element_size, int *alloc_size, int value) {
    // Adjust element size values
    (*element_size)++;
    (*a)[0] = (*element_size);

    // Expand the Vector
    if ((*element_size) >= (*alloc_size)) {
        (*alloc_size) *= 2;
        (*a) = (int *) realloc ((*a), (*alloc_size) * sizeof(int));
    }

    // Store value at Vector
    (*a)[(*element_size)] = value;

    // Print Vector Size
    printf("%d\n", (*alloc_size));

    return;
}

int pop(int **a, int *element_size, int *alloc_size) {
   // If Vector is Empty
    if ((*a)[0] == 0) {
        printf("-1\n");
        return -1;
    }

    // If Vector is Not Empty
    else {
        // Print Deleting Element
        printf("%d ", (*a)[(*element_size)]);

        // Erase Element by Adjusting Element Size
        (*element_size)--;
        (*a)[0] = (*element_size);
        
        // Adjust Vector Size if Needed
        if ((*element_size)+1 <= (*alloc_size)/2 ) {
            (*alloc_size) /= 2;
            (*a) = (int *) realloc ((*a), (*alloc_size) * sizeof(int));
        }

        printf("%d\n", (*alloc_size));
        return 0;
    }
}

int front(int *a, int element_size) {
    // If Vector is Empty
    if (a[0] == 0) {
        printf("-1\n");
        return -1;
    }

    // If Vector is Not Empty
    else {
        printf("%d\n", a[1]);
        return 0;
    }
}

int back(int *a, int element_size) {
   // If Vector is Empty
    if (a[0] == 0) {
        printf("-1\n");
        return -1;
    }

    // If Vector is Not Empty
    else {
        printf("%d\n", a[element_size]);
        return 0;
    }
}

int print_all(int *a, int element_size) {
    int i;
    
    // If Vector is Empty
    if (element_size == 0) {
        printf("-1\n");
        return -1;
    }

    // If Vector is Not Empty
    else {
        for (i = 1; i <= element_size; i++) {   // a[0] -> not value
            printf("%d ", a[i]);
        }
        printf("\n");
        return 0;
    }
}