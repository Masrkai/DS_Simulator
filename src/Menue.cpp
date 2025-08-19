//? cpp standard libraries
#include <iostream>
#include <cassert>

//? installed libraries
#include <raylib.h>

//? Files
#include"../include/StructureType.hpp"

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

    Rectangle BubbleSortButton;

    Rectangle LinearSearchButton;
    Rectangle SearchinputBox;

    // For add input
    char inputText[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    bool isInputActive = false;

    // For search input
    char searchText[MAX_INPUT_CHARS + 1] = "\0";
    int searchLetterCount = 0;
    bool isSearchActive = false;

public:

    Menu() {
        // Initialize buttons
        queueButton        = {50, 50, 120, 40};
        stackButton        = {180, 50, 120, 40};
        listButton         = {310, 50, 120, 40};

        inputBox           = {50, 100, 100, 40};

        addButton          = {160, 100, 80, 40};
        removeButton       = {250, 100, 80, 40};
        clearButton        = {340, 100, 80, 40};

        BubbleSortButton   = {550, 100, 100, 40};

        LinearSearchButton = {550, 50, 120, 40};
        SearchinputBox     = {680, 50, 100, 40};
    }

    void Update(StructureType& currentType, int& inputValue,
                            bool& shouldAdd, bool& shouldRemove, bool& shouldClear,
                            bool& shouldBubbleSort,
                            int& Target_Search_Value, bool& shouldLinearSearch) {
        Vector2 mousePoint = GetMousePosition();

        // Handle button clicks for data structure
        if (CheckCollisionPointRec(mousePoint, queueButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = StructureType::QUEUE;
        if (CheckCollisionPointRec(mousePoint, stackButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = StructureType::STACK;
        if (CheckCollisionPointRec(mousePoint, listButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            currentType = StructureType::LIST;

        // Handle input box (Add input)
        if (CheckCollisionPointRec(mousePoint, inputBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isInputActive = true;
            isSearchActive = false;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        } else if (CheckCollisionPointRec(mousePoint, SearchinputBox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isSearchActive = true;
            isInputActive = false;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            isInputActive = false;
            isSearchActive = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Typing into Add input box
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

        // Typing into Search input box
        if (isSearchActive) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= '0') && (key <= '9') && (searchLetterCount < MAX_INPUT_CHARS)) {
                    searchText[searchLetterCount] = (char)key;
                    searchText[searchLetterCount + 1] = '\0';
                    searchLetterCount++;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                searchLetterCount--;
                if (searchLetterCount < 0) searchLetterCount = 0;
                searchText[searchLetterCount] = '\0';
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

        if (CheckCollisionPointRec(mousePoint, BubbleSortButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            shouldBubbleSort = true;
        }

        // Handle linear search
        if (CheckCollisionPointRec(mousePoint, LinearSearchButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (searchLetterCount > 0) {
                Target_Search_Value = std::stoi(searchText);
                shouldLinearSearch = true;
                searchText[0] = '\0';
                searchLetterCount = 0;
            }
        }
    }

    void Draw(StructureType currentType) {
        // Draw title
        DrawText("Data Structure Simulator", 50, 10, 30, BLACK);

        // Draw buttons
        DrawRectangleRec(queueButton, (currentType == StructureType::QUEUE) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleRec(stackButton, (currentType == StructureType::STACK) ? SKYBLUE : LIGHTGRAY);
        DrawRectangleRec(listButton, (currentType == StructureType::LIST) ? SKYBLUE : LIGHTGRAY);

        DrawRectangleRec(addButton, GREEN);
        DrawRectangleRec(removeButton, RED);
        DrawRectangleRec(clearButton, ORANGE);
        DrawRectangleRec(inputBox, LIGHTGRAY);

        DrawRectangleRec(BubbleSortButton, PURPLE);
        DrawRectangleRec(LinearSearchButton, DARKBLUE);
        DrawRectangleRec(SearchinputBox, LIGHTGRAY);

        // Draw button text
        DrawText("Queue",   queueButton.x + 30,  queueButton.y + 10, 20,  BLACK);
        DrawText("Stack",   stackButton.x + 30,  stackButton.y + 10, 20,  BLACK);
        DrawText("List",    listButton.x + 40,   listButton.y + 10, 20,   BLACK);

        DrawText(inputText, inputBox.x + 10,     inputBox.y + 10, 20,     BLACK);
        DrawText(searchText, SearchinputBox.x + 10, SearchinputBox.y + 10, 20, BLACK);

        DrawText("Add",     addButton.x + 20,    addButton.y + 10, 20,    WHITE);
        DrawText("Remove",  removeButton.x + 5, removeButton.y + 10, 20, WHITE);
        DrawText("Clear",   clearButton.x + 15,  clearButton.y + 10, 20,  WHITE);

        DrawText("BubbleSort", BubbleSortButton.x + 5, BubbleSortButton.y + 10, 14, WHITE);
        DrawText("LinearSearch", LinearSearchButton.x + 5, LinearSearchButton.y + 10, 13, WHITE);

        // Draw instructions based on current data structure
        const char* instructions = "";
        switch (currentType) {
            case StructureType::QUEUE:
                instructions = "Queue: FIFO (First In, First Out) - Elements are removed from the front";
                break;
            case StructureType::STACK:
                instructions = "Stack: LIFO (Last In, First Out) - Elements are removed from the top";
                break;
            case StructureType::LIST:
                instructions = "List: Elements can be added/removed from any position";
                break;
            default:
                instructions = "Select a data structure to begin";
        }
        DrawText(instructions, 50, 150, 20, DARKGRAY);
    }
};
