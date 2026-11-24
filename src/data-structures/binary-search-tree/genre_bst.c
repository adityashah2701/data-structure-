#include "genre_bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Allocate and initialize a new BST node */
BSTNode* bst_create_node(const char *genre) {
    if (genre == NULL || genre[0] == '\0') {
        return NULL;
    }

    BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
    if (node == NULL) {
        printf("[MEMORY ERROR] Failed to allocate memory for BST node.\n");
        return NULL;
    }

    strncpy(node->genre, genre, MAX_GENRE_NAME - 1);
    node->genre[MAX_GENRE_NAME - 1] = '\0';
    node->song_count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Insert a genre category into the BST alphabetically */
BSTNode* bst_insert(BSTNode *root, const char *genre) {
    if (genre == NULL || genre[0] == '\0') {
        return root;
    }

    if (root == NULL) {
        BSTNode *new_node = bst_create_node(genre);
        printf("[BST INSERT] Created new genre category: '%s'\n", genre);
        return new_node;
    }

    int cmp = strcmp(genre, root->genre);
    if (cmp < 0) {
        root->left = bst_insert(root->left, genre);
    } else if (cmp > 0) {
        root->right = bst_insert(root->right, genre);
    } else {
        /* Duplicate genre: increment track counter */
        root->song_count++;
        printf("[BST NOTICE] Genre '%s' already exists. Track count incremented to %d.\n",
               genre, root->song_count);
    }

    return root;
}

/* Search for a genre in the BST */
BSTNode* bst_search(BSTNode *root, const char *genre) {
    if (root == NULL || genre == NULL) {
        return NULL;
    }

    int cmp = strcmp(genre, root->genre);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return bst_search(root->left, genre);
    } else {
        return bst_search(root->right, genre);
    }
}

/* Inorder Traversal: Left -> Root -> Right (Alphabetical order) */
void bst_inorder(const BSTNode *root) {
    if (root == NULL) {
        return;
    }
    bst_inorder(root->left);
    printf("  - %-18s (Songs: %d)\n", root->genre, root->song_count);
    bst_inorder(root->right);
}

/* Preorder Traversal: Root -> Left -> Right (Hierarchical tree structure) */
void bst_preorder(const BSTNode *root) {
    if (root == NULL) {
        return;
    }
    printf("  - %-18s (Songs: %d)\n", root->genre, root->song_count);
    bst_preorder(root->left);
    bst_preorder(root->right);
}

/* Postorder Traversal: Left -> Right -> Root (Bottom-up structure) */
void bst_postorder(const BSTNode *root) {
    if (root == NULL) {
        return;
    }
    bst_postorder(root->left);
    bst_postorder(root->right);
    printf("  - %-18s (Songs: %d)\n", root->genre, root->song_count);
}

/* Free all nodes in the BST to prevent memory leaks */
void bst_free(BSTNode *root) {
    if (root == NULL) {
        return;
    }
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

/* Increment song count for an existing genre, or insert if not present */
int bst_increment_song_count(BSTNode *root, const char *genre) {
    BSTNode *found = bst_search(root, genre);
    if (found != NULL) {
        found->song_count++;
        return 1;
    }
    return 0;
}
