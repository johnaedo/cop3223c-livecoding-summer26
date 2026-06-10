#ifndef INVENTORY_H
#define INVENTORY_H

/* ============================================================
   inventory.h — String-based item inventory
   Dungeon of the C Compiler | Week 3b

   INSTRUCTOR NOTE:
   This header is typed first. The key teaching point:
   - Items are char arrays (strings) — the first real use of
     strings as data in the RPG
   - MAX_ITEMS and ITEM_NAME_LEN are #define constants — introduce
     them as the way to avoid magic numbers in array sizing
   - The inventory is a 2D char array: an array of strings

   Students should recognize that char inventory[MAX_ITEMS][ITEM_NAME_LEN]
   is just an array of fixed-size char arrays — nothing magic.
   ============================================================ */

#define MAX_ITEMS      8
#define ITEM_NAME_LEN 32

/* Add item_name to inventory. Returns 1 on success, 0 if full
   or if item_name is already present. */
int  inventory_add(char inventory[][ITEM_NAME_LEN], int *count,
                   const char *item_name);

/* Remove the first occurrence of item_name. Returns 1 if found
   and removed, 0 if not found. */
int  inventory_remove(char inventory[][ITEM_NAME_LEN], int *count,
                      const char *item_name);

/* Returns 1 if item_name is in inventory, 0 otherwise. */
int  inventory_has(char inventory[][ITEM_NAME_LEN], int count,
                   const char *item_name);

/* Print all items with a header. */
void inventory_print(char inventory[][ITEM_NAME_LEN], int count);

#endif /* INVENTORY_H */
