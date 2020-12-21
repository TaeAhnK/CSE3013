/* 2.1 - Line Text Editor */

/* Allowed Header */
#include <stdio.h>
#include <stdlib.h>

/* Given Data Structure */
typedef struct node {
    char value;
    struct node* next;
    struct node* prev;
} NODE;

/* Given Function */
void left(NODE** cursor);
void right(NODE** cursor);
void del(NODE** cursor);
void add(NODE** cursor, char *data);
void quit(NODE* head);

/* Additional Function */
void printDBL(NODE** text, NODE** cursor);  // print Linked List (for Debugging)
void fprintDBL(NODE** text);                // write Linked List on file
void fprintEmpty();                         // for no input case
void freeDBL(NODE** front);                 // Free Memory for Linked List

/* Code */
int main () {
    NODE* text;             // Head of Linked List
    NODE* temp;             // to add \0
    NODE* cursor;           // Cursor Pointer 
    char cmd;               // input character
    int firstInputFlag = 0; // Check if the input is the init input

    while(1) {
        cmd = getchar();    // Get command
        if (cmd == 'L' && firstInputFlag == 1) {       // Command L
            getchar();  // \n
            left(&cursor);
        }
        else if (cmd == 'R' && firstInputFlag == 1) {   // Command R
            getchar();  // \n
            right(&cursor);
        }
        else if (cmd == 'D' && firstInputFlag == 1) {   // Command D
            getchar();  // \n
            del(&cursor);
            if (cursor->prev == NULL) { // Adjust if head has changed
                text = cursor;
            }
        }
        else if (cmd == 'A' && firstInputFlag == 1) {   // Command A
            getchar();  // blank
            cmd = getchar();
            while (cmd != '\n') {   // get letters until ENTER
                add(&cursor, &cmd);
                if (cursor == text) {   // if inserted at header
                    text = cursor->prev;
                }
                cmd = getchar();               
            }
        }
        else if (cmd == 'Q') {   // Command Q
            getchar();
            if (firstInputFlag == 0) {
                fprintEmpty();
            }
            else {
                // printDBL(&text, &cursor);   // for debugging
                fprintDBL(&text);
                freeDBL(&text);               
            }
            return 0;
        }
        else {                                         // First Input
            if (firstInputFlag == 0) {
                firstInputFlag = 1;
                // No input at first
                if (cmd == '\n') {
                    text = (NODE*) malloc (sizeof(NODE));
                    text->value = '\0';
                    text->next = NULL;
                    text->prev = NULL;
                    cursor = text;
                }
                else {
                    // Init Linked List text
                    text = (NODE*) malloc (sizeof(NODE));
                    temp = (NODE*) malloc (sizeof(NODE));
                    text->value = cmd;
                    temp->value = '\0';
                    text->next = temp;
                    text->prev = NULL;
                    temp->next = NULL;
                    temp->prev = text;

                    cursor = temp;  // cursor : points text  
                    cmd = getchar();
                    while (cmd != '\n') {   // get letters until enter
                        add(&cursor, &cmd);
                        cmd = getchar();               
                    }
                }
            }

            else {                                      // Exception
                printf("Error : Enter Command L R D A or Q\n");
            }
        }
        // printDBL(&text, &cursor); // for debugging
    }
}

void left(NODE** cursor) {
    if ((*cursor)->prev != NULL) {
        (*cursor) = (*cursor)->prev;
    }

    return;
}

void right(NODE** cursor) {
    if ((*cursor)->next != NULL) {
        (*cursor) = (*cursor)->next;
    }

    return;
}

void del(NODE** cursor) {
    // if cursor at front
    if ((*cursor)->prev == NULL) {
        return;
    } 

    NODE* p = (*cursor)->prev;

    // deleting the head
    if (p->prev == NULL) {
        (*cursor)->prev = NULL;
    }

    // else
    else {
        p->prev->next = *cursor;
        (*cursor)->prev = p->prev;
    }

    p->next = NULL;
    p->prev = NULL;
    free(p);

    return;
}

void add(NODE** cursor, char *data) {
    NODE* newNode;
    NODE* temp;
    // Make new Node
    newNode = (NODE*) malloc (sizeof(NODE));
    newNode->value = *data;

    // if not the top of text
    if ((*cursor)->prev != NULL) {
        temp = (*cursor)->prev;
        temp->next = newNode;
    }
    // if top of text
    else {
        temp = NULL;
    }

    // Adjust links
    (*cursor)->prev = newNode;
    newNode->next= (*cursor);
    newNode->prev = temp;
    
    return;
}

void printDBL(NODE** text, NODE** cursor) {
    NODE* p = *text;
    while (p != NULL) {
        if (p->value != '\0')
            printf("%c", p->value);
        p = p->next;
    }
    printf("\n%c\n", (*cursor)->value);
    return;
}

void fprintDBL(NODE** text) {
    FILE* fp;
    fp = fopen("data.txt", "w");

    NODE* p = *text;
    while (p != NULL) {
        if (p->value != '\0') {
            fprintf(fp, "%c", p->value);
        }
        p = p->next;
    }
    fclose(fp);

    return;
}

void fprintEmpty() {
    FILE* fp;
    fp = fopen("data.txt", "w");
    fclose(fp);
    return;
}

void freeDBL (NODE** front) {
    NODE* p = *front;
    while (p != NULL) {
        (*front) = (*front)->next;
        free(p);
        p = *front;
    }
}