# Music Management System – Review 2

A diploma-level Data Structures project implemented in standard **C11**.

This branch (`review-2`) implements **Review 2: Playlist and Genre Management**, building directly upon Review 1. It incorporates dynamic doubly linked lists for bidirectional playlist navigation and binary search trees for structured genre cataloging.

---

## Review 2 Overview & Implemented Functionalities

| Functionality | Data Structure | Memory Management | Description |
|---|---|---|---|
| **Song Queueing** | Linear Queue | Static Array (`MAX = 10`) | FIFO play queue with overflow/underflow handling (from Review 1). |
| **Recently Played** | Circular Queue | Static Array (`MAX = 5`) | Ring buffer storing last 5 tracks in chronological order with wraparound (from Review 1). |
| **Playlist Management** | Doubly Linked List | Dynamic Memory (`malloc`/`free`) | Insert song, remove by Song ID, forward & backward traversal, next/previous active track navigation. |
| **Genre Categories** | Binary Search Tree | Dynamic Memory (`malloc`/`free`) | Alphabetical genre organization, exact category search, and Inorder, Preorder, Postorder tree traversals. |

---

## Data Structures & Operations

### 1. Linear Queue (`linear-queue/`)
- Enqueue, dequeue, peek, display, overflow, underflow.

### 2. Circular Queue (`circular-queue/`)
- Fixed capacity 5, wraparound overwrite on full, chronological display.

### 3. Doubly Linked List (`doubly-linked-list/`)
- **Structure**: `PlaylistNode` contains `Song`, `prev`, and `next` pointers. `Playlist` maintains `head`, `tail`, `current` pointer, and `count`.
- **Operations**:
  - `playlist_add()`: Appends a new song to the tail of the list.
  - `playlist_remove_by_id()`: Traverses the list, finds matching `song.id`, adjusts neighboring pointers, updates `current`, and frees node memory.
  - `playlist_display_forward()`: Traverses from `head` to `tail`.
  - `playlist_display_backward()`: Traverses from `tail` to `head`.
  - `playlist_next()` / `playlist_prev()`: Moves the `current` pointer forwards or backwards for seamless track switching.
  - `playlist_free()`: Recursively/iteratively frees all nodes on exit to prevent memory leaks.

### 4. Binary Search Tree (`binary-search-tree/`)
- **Structure**: `BSTNode` contains `genre` string, track counter, `left`, and `right` child pointers.
- **Operations**:
  - `bst_insert()`: Inserts genre names using `strcmp`. Duplicate insertions increment the track counter.
  - `bst_search()`: Performs $O(\log N)$ average binary search for a genre.
  - `bst_inorder()`: Left $\to$ Root $\to$ Right. Produces a sorted alphabetical genre listing.
  - `bst_preorder()`: Root $\to$ Left $\to$ Right. Demonstrates root and subtree hierarchical layout.
  - `bst_postorder()`: Left $\to$ Right $\to$ Root. Displays bottom-up reduction.
  - `bst_free()`: Postorder deallocation of all dynamically allocated tree nodes.

---

## Time Complexities

| Operation | Linear Queue | Circular Queue | Doubly Linked List | Binary Search Tree (Avg / Worst) |
|---|---|---|---|---|
| **Insertion** | $O(1)$ | $O(1)$ | $O(1)$ (at tail) | $O(\log N)$ / $O(N)$ |
| **Deletion** | $O(1)$ | $O(1)$ | $O(N)$ (search & unlink) | $O(\log N)$ / $O(N)$ |
| **Search / Lookup** | $O(N)$ | $O(N)$ | $O(N)$ | $O(\log N)$ / $O(N)$ |
| **Traversal / Display** | $O(N)$ | $O(N)$ | $O(N)$ (Forward/Backward) | $O(N)$ (In/Pre/Post-order) |

---

## Folder Structure on `review-2`

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
        └── binary-search-tree/
            ├── genre_bst.h
            └── genre_bst.c
```

---

## Compilation & Execution

Compile using `gcc -std=c11 -Wall -Wextra -Wpedantic`:

```bash
# Compile
make

# Run
make run

# Clean build artifacts
make clean
```
