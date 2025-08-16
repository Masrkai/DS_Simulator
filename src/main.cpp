//? cpp standard libraries
#include <iostream>
#include <cassert>
#include <vector>

//? installed libraries
#include <raylib.h>

//? Files
#include"Menue.cpp"
#include"Visualizer.cpp"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Data Structure Educational Simulator");
    SetTargetFPS(60);

    Menu menu;
    DataStructureVisualizer visualizer;
    DataStructureType currentType = DataStructureType::NONE;

    int inputValue = 0;
    bool shouldAdd = false;
    bool shouldRemove = false;
    bool shouldClear = false;

    while (!WindowShouldClose()) {
        // Update
        menu.Update(currentType, inputValue, shouldAdd, shouldRemove, shouldClear);
        visualizer.Update();

        if (shouldAdd) {
            visualizer.AddNode(inputValue);
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

        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            menu.Draw(currentType);
            if (currentType != DataStructureType::NONE)
                visualizer.Draw(currentType);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}