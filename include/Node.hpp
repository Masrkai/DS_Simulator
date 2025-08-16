#pragma once

//? installed libraries
#include <raylib.h>


// Node structure for visualization
struct Node {
    int value;
    Vector2 position;
    Color color;
    float alpha;

    Node(int val, Vector2 pos) : value(val), position(pos), color(BLUE), alpha(1.0f) {}
};