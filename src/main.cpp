//? cpp standard libraries
#include <iostream>
// #include <cassert>
// #include <vector>

//? installed libraries
#include <raylib.h>

//? Files
#include"Menue.cpp"
#include"Visualizer.cpp"
#include "../include/Sorting/Bubble_sort.cpp"





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
    bool shouldBubbleSort = false;   // <-- missing


    while (!WindowShouldClose()) {
        // Update
        menu.Update(currentType, inputValue, shouldAdd, shouldRemove, shouldClear, shouldBubbleSort);
        visualizer.Update();

        if (shouldAdd) {
            visualizer.AddNode(inputValue, currentType);
            shouldAdd = false;
        }

        if (shouldRemove) {
            visualizer.RemoveNode(currentType);
            shouldRemove = false;
        }

        if (shouldClear) {
            visualizer.Clear();
            shouldClear = false;
        }

        if (shouldBubbleSort) {
            shouldBubbleSort = false;
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