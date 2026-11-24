#ifndef GENRE_BST_H
#define GENRE_BST_H

#include "../../../common/song.h"

#define MAX_GENRE_NAME 32

/*
 * Binary Search Tree Node
 * Represents a musical genre category in the catalog.
 * Organized lexicographically (alphabetical order).
 */
typedef struct BSTNode {
    char genre[MAX_GENRE_NAME];
    int song_count;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

/* Function Declarations */
BSTNode* bst_create_node(const char *genre);
BSTNode* bst_insert(BSTNode *root, const char *genre);
BSTNode* bst_search(BSTNode *root, const char *genre);
void bst_inorder(const BSTNode *root);
void bst_preorder(const BSTNode *root);
void bst_postorder(const BSTNode *root);
void bst_free(BSTNode *root);
int bst_increment_song_count(BSTNode *root, const char *genre);

#endif /* GENRE_BST_H */
