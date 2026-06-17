/* ============================================================
   inventory.c — String-based inventory implementation
   Dungeon of the C Compiler | Week 3b

   INSTRUCTOR CHECKPOINTS:

   CHECKPOINT A — inventory_print
     - inventory[i] is a char* (pointer to i-th row of 2D array)
     - %s prints until '\0' — same null terminator they learned

   CHECKPOINT B — inventory_has
     Why not == ? Because == compares addresses, not content.

   CHECKPOINT C — inventory_add
     Combines has() with strncpy.
     - Check for duplicates first (call has())
     - Check for full inventory
     - strncpy + manual null termination
     - Incrementing *count through the pointer

   CHECKPOINT D — inventory_remove
     When we remove from the middle, we have a hole. We fill it
      by copying each subsequent element one position earlier.
   ============================================================ */

#include <stdio.h>
#include <string.h>
#include "inventory.h"

/* ── inventory_print ───────────────────────────────────────── */
/* CHECKPOINT A — type this first */
void inventory_print(char inventory[][ITEM_NAME_LEN], int count) {
    printf("┌─────────────────────────┐\n");
    printf("│ Inventory (%d/%d)       │\n", count, MAX_ITEMS);
    printf("├─────────────────────────┤\n");
    if (count == 0) {
        printf("│ (empty)                 │\n");
    } else {
        for (int i = 0; i < count; i++) {
            /* inventory[i] is a char* — pointer to the i-th string */
            printf("│ %-2d. %-20s │\n", i + 1, inventory[i]);
        }
    }
    printf("└─────────────────────────┘\n");
}

/* ── inventory_has ─────────────────────────────────────────── */
/* CHECKPOINT B — demonstrate the == vs strcmp distinction */
int inventory_has(char inventory[][ITEM_NAME_LEN], int count,
                  const char *item_name) {
    for (int i = 0; i < count; i++) {
        /* strcmp returns 0 when strings are equal */
        if (strcmp(inventory[i], item_name) == 0) {
            return 1;
        }
    }
    return 0;
}

/* ── inventory_add ─────────────────────────────────────────── */
/* CHECKPOINT C — strncpy, null termination, output pointer *count */
int inventory_add(char inventory[][ITEM_NAME_LEN], int *count,
                  const char *item_name) {
    /* Full? */
    if (*count >= MAX_ITEMS) {
        printf("Inventory full!\n");
        return 0;
    }
    /* Already have it? */
    if (inventory_has(inventory, *count, item_name)) {
        printf("Already carrying %s.\n", item_name);
        return 0;
    }

    /* Safe copy with guaranteed null termination */
    strncpy(inventory[*count], item_name, ITEM_NAME_LEN - 1);
    inventory[*count][ITEM_NAME_LEN - 1] = '\0';

    /* Increment through the pointer — *count in main() updates */
    (*count)++;
    return 1;
}

/* ── inventory_remove ──────────────────────────────────────── */
/* CHECKPOINT D — array compaction by shifting */
int inventory_remove(char inventory[][ITEM_NAME_LEN], int *count,
                     const char *item_name) {
    /* Find it */
    int found = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(inventory[i], item_name) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) return 0;   /* not found */

    /* Shift everything after `found` one position left */
    for (int i = found; i < *count - 1; i++) {
        strncpy(inventory[i], inventory[i + 1], ITEM_NAME_LEN);
    }

    /* Clear the now-duplicate last slot */
    inventory[*count - 1][0] = '\0';
    (*count)--;
    return 1;
}
