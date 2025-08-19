//? cpp standard libraries
#include <iostream>

//? installed libraries
#include <raylib.h>

//? Files
#include "Menue.cpp"
#include "Visualizer.cpp"
#include "../include/Sorting/Bubble_sort.cpp"
#include "../include/LinkedList.hpp"
#include "../include/Searching/Linear_search.cpp"   // ✅ add linear search

// Global linked list instance
LinkedList<int> globalList;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Data Structure Educational Simulator");
    SetTargetFPS(60);

    Menu menu;
    DataStructureVisualizer visualizer;
    StructureType currentType = StructureType::NONE;

    int inputValue = 0;
    bool shouldAdd = false;
    bool shouldRemove = false;
    bool shouldClear = false;
    bool shouldBubbleSort = false;

    int targetSearchValue = 0;     // ✅ value to search for
    bool shouldLinearSearch = false;

    while (!WindowShouldClose()) {
        // Update (pass search values too)
        menu.Update(
            currentType,
            inputValue,
            shouldAdd,
            shouldRemove,
            shouldClear,
            shouldBubbleSort,
            targetSearchValue,
            shouldLinearSearch
        );

        visualizer.Update();

        if (shouldAdd) {
            globalList.append(inputValue);                    // add to linked list
            visualizer.LoadFromList(globalList, currentType); // sync visuals
            shouldAdd = false;
        }

        if (shouldRemove) {
            globalList.removeFirst();                         // remove from head
            visualizer.LoadFromList(globalList, currentType);
            shouldRemove = false;
        }

        if (shouldClear) {
            globalList.clear();                               // clear linked list
            visualizer.LoadFromList(globalList, currentType);
            shouldClear = false;
        }

        if (shouldBubbleSort) {
            bubble_sort(globalList);                          // sort linked list
            visualizer.LoadFromList(globalList, currentType);
            shouldBubbleSort = false;
        }

        if (shouldLinearSearch) {
            // ✅ perform linear search
            int index = linearSearch(globalList, targetSearchValue);

            if (index != -1) {
                std::cout << "Value " << targetSearchValue
                          << " found at index " << index << std::endl;

                // You might want to highlight node in visualizer here:
                visualizer.HighlightNode(index);

            } else {
                std::cout << "Value " << targetSearchValue << " not found." << std::endl;
            }

            shouldLinearSearch = false;
        }

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            menu.Draw(currentType);
            if (currentType != StructureType::NONE)
                visualizer.Draw(currentType);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
