// ***
// *** You MUST modify this file
// ***

#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** INTERFACE FUNCTIONS **/

int comparePaths(char* p1, char* p2) {
    // Rule 1: Length
    int len1 = strlen(p1);
    int len2 = strlen(p2);
    if (len1 != len2) return len1 - len2;

    // Rule 2: Turns
    int turns1 = 0, turns2 = 0;
    for (int i = 1; i < len1; i++) {
        if (p1[i] != p1[i-1]) turns1++;
        if (p2[i] != p2[i-1]) turns2++;
    }
    if (turns1 != turns2) return turns1 - turns2;

    // Rule 3: Alphabetical
    return strcmp(p1, p2);
}

PathLL* buildPaths() {
    PathLL* retval = malloc(sizeof(PathLL));
    retval->head = NULL;
    return retval;
}

// Read the comments in list.h to understand what you need to implement
// for each function.
// Remember to check for memory leak.



void freePaths(PathLL* p) {
    // Remove all nodes from a linked list, deallocate the PathLL structure.
    // TODO
    if (p == NULL) return;
    PathNode* current = p->head;
    while (current != NULL) {
        PathNode* temp = current;
        current = current->next;
        freeNode(temp);
    }
    free(p);
}

PathNode* buildNode(char* path) {
    // Allocate a new PathNode with path as its data, return the address.

    // WARNING: don't forget to use strcpy to copy path into the new node.
    // Don't just set them equal, otherwise if the input path changes the node
    // will have the wrong path.

    // TODO
    PathNode* newNode = malloc(sizeof(PathNode));
    if (newNode == NULL) return NULL;

    newNode->path = malloc(strlen(path) + 1);
    if (newNode->path == NULL) {
        free(newNode);
        return NULL;
    }

    strcpy(newNode->path, path);
    newNode->next = NULL;
    return newNode;
}

void freeNode(PathNode* p) {
    // Deallocate a pathNode
    // TODO
    if (p) {
        free(p->path);
        free(p);
    }
}

bool addNode(PathLL* paths, char* path) {
    // Add a path to the list of paths
    // TODO
    PathNode* newNode = buildNode(path);
    if (!newNode) return false;

    PathNode* curr = paths->head;
    PathNode* prev = NULL;

    // Find insertion point based on comparePaths logic
    while (curr != NULL && comparePaths(curr->path, path) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (prev == NULL) { // Insert at head
        newNode->next = paths->head;
        paths->head = newNode;
    } else {
        newNode->next = curr;
        prev->next = newNode;
    }
    return true;
}

bool removeNode(PathLL* paths, char* path) {
    // Remove a node from the list with the specified path
    // TODO
    PathNode* curr = paths->head;
    PathNode* prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->path, path) == 0) {
            if (prev == NULL) paths->head = curr->next;
            else prev->next = curr->next;
            freeNode(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool containsNode(PathLL* paths, char* path) {
    // Return true if path exists in the list
    // TODO
    PathNode* curr = paths->head;
    while (curr != NULL) {
        if (strcmp(curr->path, path) == 0) return true;
        curr = curr->next;
    }
    return false;
}

void printPaths(PathLL* paths, FILE* fptr) {
    PathNode* curr = paths->head;
    int i = 0;
    while (curr != NULL) {
        fprintf(fptr, "Path %2d: %s\n", i, curr->path);
        i++;
        curr = curr->next;
    }
}
