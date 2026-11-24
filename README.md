# Music Management System – C Data Structures Project

A modular, diploma-level Data Structures project implemented in standard **C11**. The system models a music player and manager across three academic evaluation reviews, progressively introducing fundamental data structures.

## Academic Review Roadmap

| Review | Branch | Data Structures Implemented | Focus Functionalities |
|---|---|---|---|
| **Base** | `main` | Common definitions & Project scaffold | Data models, safe I/O utilities |
| **Review 1** | `review-1` | Linear Queue, Circular Queue | Song queueing (FIFO), Recently played history (wraparound overwrite) |
| **Review 2** | `review-2` | Doubly Linked List, Binary Search Tree | Playlist management (bidirectional traversal), Genre categorization |
| **Review 3** | `review-3` | Hash Table (with linear probing & tombstones) | Fast ID lookup, Complete end-to-end integration |

## Data Structures Overview

1. **Linear Queue (`linear_queue`)**: FIFO play queue managing upcoming songs. Handles overflow and underflow conditions.
2. **Circular Queue (`circular_queue`)**: Ring buffer storing the latest 5 recently played tracks, automatically overwriting the oldest song on wraparound.
3. **Doubly Linked List (`playlist`)**: User playlist allowing forward/backward navigation and song deletion by unique ID.
4. **Binary Search Tree (`genre_bst`)**: Hierarchical genre directory providing sorted (inorder), preorder, and postorder traversals and search.
5. **Hash Table (`hash_table`)**: Closed addressing / open hashing with linear probing and tombstone markers for $O(1)$ song lookup, insertion, and deletion.

## Modular Folder Structure

```text
Music-Management-System/
│
├── README.md
├── Makefile
├── .gitignore
│
├── common/
│   ├── song.h
│   └── input.h
│
└── src/
    ├── main.c
    │
    └── data-structures/
        ├── linear-queue/
        │   ├── linear_queue.h
        │   └── linear_queue.c
        │
        ├── circular-queue/
        │   ├── circular_queue.h
        │   └── circular_queue.c
        │
        ├── doubly-linked-list/
        │   ├── playlist.h
        │   └── playlist.c
        │
        ├── binary-search-tree/
        │   ├── genre_bst.h
        │   └── genre_bst.c
        │
        └── hash-table/
            ├── hash_table.h
            └── hash_table.c
```

## Compilation and Execution

- `make` - Compiles the project with standard flags (`gcc -std=c11 -Wall -Wextra -Wpedantic`).
- `make run` - Executes the compiled binary `./music_system`.
- `make clean` - Cleans object files and binaries.
