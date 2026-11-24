# Music Management System – Review 3 (Complete Integration)

A complete diploma-level Data Structures project implemented in standard **C11**.

This branch (`review-3`) represents the final state of the project, delivering the complete, integrated **Music Management System** across all five fundamental data structures.

---

## Academic Review Roadmap & Evolution

| Review | Branch | Data Structures Implemented | Focus Functionalities |
|---|---|---|---|
| **Review 1** | `review-1` | Linear Queue, Circular Queue | Song queueing (FIFO), Recently played history (wraparound overwrite) |
| **Review 2** | `review-2` | Doubly Linked List, Binary Search Tree | Playlist management (bidirectional traversal), Genre categorization |
| **Review 3** | `review-3` | **Hash Table** + All 5 Integrated | Fast $O(1)$ ID search, Tombstone deletion, Unified end-to-end integration |

---

## All Five Required Data Structures

| Functionality | Data Structure | Storage / Memory | Primary Operations |
|---|---|---|---|
| **Song Queueing** | **Linear Queue** | Static Array (`MAX = 10`) | Enqueue, Dequeue, Peek, Display, Overflow & Underflow handling. |
| **Recently Played** | **Circular Queue** | Static Array (`MAX = 5`) | Enqueue recently played tracks, wraparound overwrite of oldest track on overflow, chronological display. |
| **Playlist Management**| **Doubly Linked List** | Dynamic (`malloc`/`free`) | Add song, Remove by Song ID, Forward traversal (Head $\to$ Tail), Backward traversal (Tail $\to$ Head), Next / Previous track navigation. |
| **Genre Categories** | **Binary Search Tree** | Dynamic (`malloc`/`free`) | Alphabetical genre insertion, Search, Inorder (sorted), Preorder, and Postorder traversals. |
| **Song ID Lookup** | **Hash Table** | Static Array (`SIZE = 11`) | Array-based open addressing with linear probing, duplicate ID prevention, collision resolution, and tombstone deletion. |

---

## Detailed Data Structure Implementations

### 1. Linear Queue (`linear-queue/`)
- **Role**: FIFO song queue buffer for tracks waiting to be played.
- **Underflow**: Triggered when attempting to dequeue from an empty queue (`front == -1 || front > rear`).
- **Overflow**: Triggered when `rear == MAX_LINEAR_QUEUE - 1`.
- **Reset**: When all songs are dequeued (`front > rear`), `front` and `rear` reset to `-1` to reuse space.

### 2. Circular Queue (`circular-queue/`)
- **Role**: Fixed-size circular buffer maintaining the **5 most recently played songs**.
- **Wraparound Overwrite**: When 5 songs are stored, a new play increments `rear = (rear + 1) % 5`, places the song, and increments `front = (front + 1) % 5`, overwriting the oldest song.
- **Chronological Display**: Iterates from `front` across `count` elements with `(front + i) % 5` to list history in order of playback from oldest to newest.

### 3. Doubly Linked List (`doubly-linked-list/`)
- **Role**: User-curated custom playlist with bidirectional playback.
- **Pointers**: Each node contains `prev` and `next` pointers. The playlist tracks `head`, `tail`, and `current` (active track).
- **Deletion by ID**: Finds matching `song.id`, patches neighboring node pointers (`prev->next = next`, `next->prev = prev`), updates `current`, and frees allocated memory.
- **Navigation**: Supports moving to `next` and `prev` songs directly.

### 4. Binary Search Tree (`binary-search-tree/`)
- **Role**: Hierarchical directory of music genres.
- **Ordering**: Lexicographical order via `strcmp()`.
- **Traversals**:
  - **Inorder** (Left, Root, Right): Displays genres in alphabetical order.
  - **Preorder** (Root, Left, Right): Displays tree root before children.
  - **Postorder** (Left, Right, Root): Displays subtrees before root.

### 5. Hash Table (`hash-table/`)
- **Role**: Instant $O(1)$ search, insertion, and deletion of songs by unique integer `Song ID`.
- **Hash Function**: Division method: `hash(id) = id % 11`.
- **Collision Resolution**: Open addressing with **Linear Probing**: `index = (hash(id) + i) % 11`.
- **Duplicate ID Handling**: Checks existing occupied slots during probe; duplicate IDs are rejected.
- **Tombstones (`SLOT_DELETED`)**:
  - When a song is deleted, its slot is marked as a **tombstone** rather than empty.
  - Probing during searches continues past tombstones to maintain lookup chains for collided entries.
  - New insertions reuse available tombstone slots.
- **Physical Layout Visualization**: Displays each slot, its status (`[EMPTY]`, `[OCCUPIED]`, or `[TOMBSTONE]`), and probed placement.

---

## System Integration Workflow

```
[Register Song] ───► [Hash Table (Catalog)] ───► [Genre BST (Category)]
                            │
              ┌─────────────┴─────────────┐
              ▼                           ▼
     [Linear Queue (FIFO)]     [Doubly Linked List (Playlist)]
              │                           │
         Play Next                   Next / Prev
              │                           │
              └───────────┬───────────────┘
                          ▼
            [Circular Queue (Recently Played)]
              (Wraparound: Latest 5 Tracks)
```

1. **Register**: Songs are entered once into the system and indexed in the Hash Table catalog and Genre BST.
2. **Queueing**: Tracks from the catalog are enqueued into the Linear Queue.
3. **Playback Transition**: Playing a queued song removes it from the Linear Queue (`lq_dequeue`) and immediately registers it into the Recently Played Circular Queue (`cq_insert`).
4. **Consistent IDs**: The same `Song ID` references identical metadata across all modules.

---

## Time Complexity Summary

| Data Structure | Operation | Average Complexity | Worst Case | Space Complexity |
|---|---|---|---|---|
| **Linear Queue** | Enqueue / Dequeue | $O(1)$ | $O(1)$ | $O(N)$ (Static) |
| **Circular Queue** | Insert / Overwrite | $O(1)$ | $O(1)$ | $O(1)$ (Fixed $N=5$) |
| **Doubly Linked List** | Add to End | $O(1)$ | $O(1)$ | $O(N)$ (Dynamic) |
| | Remove by ID | $O(N)$ | $O(N)$ | |
| | Forward / Backward Display | $O(N)$ | $O(N)$ | |
| **Binary Search Tree** | Insert Genre | $O(\log N)$ | $O(N)$ | $O(N)$ (Dynamic) |
| | Search Genre | $O(\log N)$ | $O(N)$ | |
| | Traversals (In/Pre/Post) | $O(N)$ | $O(N)$ | |
| **Hash Table** | Search by Song ID | $O(1)$ | $O(N)$ | $O(M)$ (Static Table) |
| | Insert Song | $O(1)$ | $O(N)$ | |
| | Delete (Tombstone) | $O(1)$ | $O(N)$ | |

---

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

---

## Compilation & Execution

Compile using `gcc -std=c11 -Wall -Wextra -Wpedantic`:

```bash
# Compile the project
make

# Execute the application
make run

# Clean build artifacts
make clean
```
