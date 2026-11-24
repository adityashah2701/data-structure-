# Music Management System – Review 1

A diploma-level Data Structures project implemented in standard **C11**.

This branch (`review-1`) implements **Review 1: Queue Operations**, focusing on FIFO song queueing and fixed-capacity circular history buffering.

---

## Review 1 Overview & Implemented Functionalities

| Functionality | Data Structure | Implementation Type | Description |
|---|---|---|---|
| **Song Queueing** | Linear Queue | Static Array (`MAX = 10`) | FIFO play queue. Supports enqueue, dequeue, peek, display, overflow, and underflow detection. |
| **Recently Played** | Circular Queue | Static Array (`MAX = 5`) | Ring buffer storing the last 5 played tracks in chronological order. Automatically handles wraparound and overwrites the oldest track. |

---

## Data Structures & Operations

### 1. Linear Queue (`linear-queue/`)
- **Structure**: Static array of `Song` elements with `front` and `rear` index pointers.
- **Operations**:
  - `lq_init()`: Initializes `front = -1` and `rear = -1`.
  - `lq_enqueue()`: Adds song to `rear`. Checks for queue overflow (`rear == MAX - 1`).
  - `lq_dequeue()`: Removes song from `front`. Checks for underflow (`front == -1 || front > rear`). Resets to `-1` when emptied.
  - `lq_display()`: Prints all waiting songs from `front` to `rear`.
  - `lq_peek()`: Inspects the next upcoming track without removing it.

### 2. Circular Queue (`circular-queue/`)
- **Structure**: Ring buffer array of fixed size `5` with `front`, `rear`, and `count`.
- **Operations**:
  - `cq_init()`: Initializes `front = -1`, `rear = -1`, `count = 0`.
  - `cq_insert()`: Adds newly played track. If count reaches 5, overwrites the item at `front` and advances `front = (front + 1) % 5`, preserving the latest 5 songs.
  - `cq_display()`: Iterates `(front + i) % 5` for `i` from `0` to `count - 1` to display tracks in strictly chronological order (oldest to newest).

---

## Time Complexities

| Operation | Linear Queue | Circular Queue |
|---|---|---|
| **Enqueue / Insert** | $O(1)$ | $O(1)$ |
| **Dequeue** | $O(1)$ | $O(1)$ |
| **Peek** | $O(1)$ | $O(1)$ |
| **Display All** | $O(N)$ | $O(N)$ |

---

## Folder Structure on `review-1`

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
        └── circular-queue/
            ├── circular_queue.h
            └── circular_queue.c
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
