//? cpp standard libraries
#include <iostream>
#include <cassert>

//? installed libraries
#include <raylib.h>

//? Files
#include"../include/DataStructureType.hpp"

const int MAX_INPUT_CHARS = 3;

// Menu class to handle UI
class Menu {
private:
    Rectangle queueButton;
    Rectangle stackButton;
    Rectangle listButton;

    Rectangle inputBox;

    Rectangle addButton;
    Rectangle removeButton;
    Rectangle clearButton;

    char inputText[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    bool isInputActive = false;

public:

    Menu() {
        // Initialize buttons
        queueButton  = {50, 50, 120, 40};
        stackButton  = {180, 50, 120, 40};
        listButton   = {310, 50, 120, 40};

        inputBox     = {50, 100, 100, 40};

        addButton    = {160, 100, 80, 40};
        removeButton = {250, 100, 80, 40};
        clearButton  = {340, 100, 80, 40};
    }

    void Update(DataStructureType& currentType, int& inputValue, bool& shouldAdd, bool& shouldRemove, bool& shouldClear) {
        Vector2 mousePoint = GetMousePosition();

        // Handle button clicks
        if (CheckCollisionPointRec(mousePoint, queueButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = DataStructureType::QUEUE;
        if (CheckCollisionPointRec(mousePoint, stackButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = DataStructureType::STACK;
        if (CheckCollisionPointRec(mousePoint, listButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = DataStructureType::LIST;

        // Handle input box
        if (CheckCollisionPointRec(mousePoint, inputBox)) {
            isInputActive = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isInputActive = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (isInputActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= '0') && (key <= '9') && (letterCount < MAX_INPUT_CHARS)) {
                    inputText[letterCount] = (char)key;
                    inputText[letterCount + 1] = '\0';
                    letterCount++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                inputText[letterCount] = '\0';
            }
        }

        // Handle operation buttons
        if (CheckCollisionPointRec(mousePoint, addButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (letterCount > 0) {
                inputValue = std::stoi(inputText);
                shouldAdd = true;
                inputText[0] = '\0';
                letterCount = 0;
            }
        }

        if (CheckCollisionPointRec(mousePoint, removeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            shouldRemove = true;

        if (CheckCollisionPointRec(mousePoint, clearButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            shouldClear = true;
    }

    void Draw(DataStructureType currentType) {
        // Draw title
        DrawText("Data Structure Simulator", 50, 10, 30, BLACK);

        // Draw buttons
        DrawRectangleRec(queueButton, (currentType == DataStructureType::QUEUE) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleRec(stackButton, (currentType == DataStructureType::STACK) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleRec(listButton, (currentType == DataStructureType::LIST) ? SKYBLUE : LIGHTGRAY);

        DrawRectangleRec(addButton, GREEN);

        DrawRectangleRec(removeButton, RED);
        DrawRectangleRec(clearButton, ORANGE);
        DrawRectangleRec(inputBox, LIGHTGRAY);

        // Draw button text
        DrawText("Queue",   queueButton.x + 30,  queueButton.y + 10, 20,  BLACK);
        DrawText("Stack",   stackButton.x + 30,  stackButton.y + 10, 20,  BLACK);
        DrawText("List",    listButton.x + 40,   listButton.y + 10, 20,   BLACK);

        DrawText("Add",     addButton.x + 20,    addButton.y + 10, 20,    WHITE);
        DrawText("Remove",  removeButton.x + 10, removeButton.y + 10, 20, WHITE);
        DrawText("Clear",   clearButton.x + 15,  clearButton.y + 10, 20,  WHITE);

        DrawText(inputText, inputBox.x + 10,     inputBox.y + 10, 20,     BLACK);

        // Draw instructions based on current data structure
        const char* instructions = "";
        switch (currentType) {
            case DataStructureType::QUEUE:
                instructions = "Queue: FIFO (First In, First Out) - Elements are removed from the front";
                break;
            case DataStructureType::STACK:
                instructions = "Stack: LIFO (Last In, First Out) - Elements are removed from the top";
                break;
            case DataStructureType::LIST:
                instructions = "List: Elements can be added/removed from any position";
                break;
            default:
                instructions = "Select a data structure to begin";
        }
        DrawText(instructions, 50, 150, 20, DARKGRAY);
    }
};
