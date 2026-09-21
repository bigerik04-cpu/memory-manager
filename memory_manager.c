/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 *
 * This program implements a dynamic game inventory system to practice
 * manual memory management using malloc, calloc, realloc, and free.
 *
 * You'll experience memory leaks and dangling pointers firsthand,
 * then systematically fix each error.
 */

#include <stdio.h>
#include <stdlib.h>

// =============================================================================
// PART 1: CREATE INVENTORY
// =============================================================================

void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");

    int inventory_size = 5;
    int *item_ids = NULL;
    int *quantities = NULL;

    // Allocate memory for item_ids array
    item_ids = (int*)malloc(inventory_size * sizeof(int));

    // Check if malloc succeeded
    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    // Allocate memory for quantities array
    quantities = (int*)malloc(inventory_size * sizeof(int));

    // Check if malloc succeeded
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill the inventory with starting items
    printf("Starting inventory:\n");

    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;
        quantities[i] = (i + 1) * 10;

        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    // Free allocated memory
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 2: EXPAND INVENTORY
// =============================================================================

void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");

    int initial_size = 3;
    int expanded_size = 6;

    int *item_ids = NULL;
    int *quantities = NULL;

    // Allocate initial item_ids array
    item_ids = (int*)malloc(initial_size * sizeof(int));

    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    // Allocate initial quantities array
    quantities = (int*)malloc(initial_size * sizeof(int));

    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        return;
    }

    // Fill initial inventory
    printf("Initial inventory (size %d):\n", initial_size);

    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);

        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    printf("\nPlayer acquires more items! Expanding inventory...\n");

    // Expand item_ids safely
    int *new_item_ids =
        (int*)realloc(item_ids, expanded_size * sizeof(int));

    if (new_item_ids == NULL) {
        printf("Failed to expand item_ids\n");

        free(item_ids);
        free(quantities);

        return;
    }

    item_ids = new_item_ids;

    // Expand quantities safely
    int *new_quantities =
        (int*)realloc(quantities, expanded_size * sizeof(int));

    if (new_quantities == NULL) {
        printf("Failed to expand quantities\n");

        free(item_ids);
        free(quantities);

        return;
    }

    quantities = new_quantities;

    // Add new items
    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }

    // Print expanded inventory
    printf("Expanded inventory (size %d):\n", expanded_size);

    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n",
               item_ids[i], quantities[i]);
    }

    // Free allocated memory
    free(item_ids);
    free(quantities);

    printf("Memory freed successfully.\n");
}

// =============================================================================
// PART 3: MEMORY LEAK DEMONSTRATION
// =============================================================================

void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMONSTRATION ===\n");
    printf("Allocating memory in a loop WITHOUT freeing...\n");

    for (int i = 0; i < 1000; i++) {

        int *temp_item =
            (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;

        // Intentionally not freed.
        // This demonstrates a memory leak.
    }

    printf(
        "Loop complete. Leaked approximately %zu KB of memory.\n",
        (1000 * 1000 * sizeof(int)) / 1024
    );

    printf(
        "This memory cannot be reused until the program ends.\n"
    );
}

// =============================================================================
// PART 3B: FIXED VERSION - NO MEMORY LEAK
// =============================================================================

void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION - NO MEMORY LEAK ===\n");

    printf(
        "Allocating memory in a loop WITH proper freeing...\n"
    );

    for (int i = 0; i < 1000; i++) {

        int *temp_item =
            (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;

        // Free memory after we finish using it
        free(temp_item);
    }

    printf(
        "Loop complete. Memory properly freed after each use.\n"
    );

    printf(
        "Total memory allocated and freed: %zu KB\n",
        (1000 * 1000 * sizeof(int)) / 1024
    );
}

// =============================================================================
// PART 4: SAFE POINTER HANDLING
// =============================================================================

void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");

    int *player_health =
        (int*)malloc(sizeof(int));

    if (player_health == NULL) {
        printf("Allocation failed!\n");
        return;
    }

    *player_health = 100;

    printf("Player health: %d\n", *player_health);

    // Free memory
    free(player_health);

    printf("Health memory freed.\n");

    // Avoid dangling pointer
    player_health = NULL;

    // Check pointer before dereferencing
    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    }
    else {
        printf("Health data not available\n");
    }

    printf("Safe pointer handling complete.\n");
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {

    printf("=============================================================\n");
    printf("      MEMORY MANAGER: Dynamic Inventory System\n");
    printf("=============================================================\n");

    // Part 1
    create_inventory();

    // Part 2
    expand_inventory();

    // Part 3
    printf("\n--- First, observe the memory leak ---\n");

    memory_leak_demo();

    printf("\n--- Now, see the properly managed version ---\n");

    memory_leak_fixed();

    // Part 4
    safe_pointer_handling();

    printf("\n=============================================================\n");
    printf("Memory management complete!\n");

    printf(
        "Review your code for proper malloc/free pairing and NULL checks.\n"
    );

    printf("=============================================================\n");

    return 0;
}