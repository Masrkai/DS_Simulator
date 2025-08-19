//? cpp standard libraries
#include <iostream>
#include <cassert>
#include <vector>

//? installed libraries
#include <raylib.h>

//? Files
#include "../include/Node.hpp"
#include "../include/StructureType.hpp"
#include "../include/Queue.hpp"
#include "../include/Stack.hpp"
#include "../include/LinkedList.hpp"

// Constants
const int SCREEN_WIDTH = 920;
const int SCREEN_HEIGHT = 920;

class DataStructureVisualizer {
public:

    std::vector<Node> nodes;
    Queue<Node> animatingNodes;

    Vector2 startPosQueue   = {200, 600};
    Vector2 startPosStack   = {200, 600};
    Vector2 startPosList    = {200, 600};

    float spacing = 100;

    void UpdateNodePositions(StructureType type) {
        for (int i = 0; i < nodes.size(); i++) {
            if (type == StructureType::QUEUE) {
                nodes[i].position = { startPosQueue.x + i * spacing, startPosQueue.y };
            }
            else if (type == StructureType::STACK) {
                nodes[i].position = { startPosStack.x, startPosStack.y - i * spacing };
            }
            else if (type == StructureType::LIST) {
                nodes[i].position = { startPosList.x + i * spacing, startPosList.y };
            }
        }
    }

    // Rebuild the visual nodes from the linked list model
    void LoadFromList(const LinkedList<int>& list, StructureType type) {
        nodes.clear();

        // If head is public (like your bubble_sort assumes), traverse directly.
        auto cur = list.head;
        while (cur) {
            nodes.push_back(Node(cur->data, {0, 0}));
            cur = cur->next;
        }

        UpdateNodePositions(type);
    }

    void AddNode(int value, StructureType type) {
        nodes.push_back(Node(value, {0,0}));  // temporary position
        UpdateNodePositions(type);
    }

    void RemoveNode(StructureType type) {
        if (nodes.empty()) return;

        Node removed = (type == StructureType::STACK) ? nodes.back() : nodes.front();
        removed.color = RED;
        animatingNodes.enqueue(removed);

        if (type == StructureType::STACK)
            nodes.pop_back();
        else
            nodes.erase(nodes.begin());

        UpdateNodePositions(type);
    }

    void Clear() {
        nodes.clear();
        animatingNodes.clear();
    }

    void Update() {
        int size = animatingNodes.size();
        for (int i = 0; i < size; i++) {
            Node node = animatingNodes.getFront();
            animatingNodes.dequeue();

            node.alpha -= 0.04f;
            node.position.y -= 2.0f;

            if (node.alpha > 0) animatingNodes.enqueue(node);
        }
    }

    void Draw(StructureType type) {
        // Layout correction
        UpdateNodePositions(type);

        for (int i = 0; i < nodes.size(); i++) {
            const Node &node = nodes[i];

            DrawCircle(node.position.x, node.position.y, 30, node.color);

            std::string valueStr = std::to_string(node.value);
            DrawText(valueStr.c_str(),
                     node.position.x - MeasureText(valueStr.c_str(), 20) / 2,
                     node.position.y - 10,
                     20,
                     WHITE);

            if (i < nodes.size() - 1) {
                if (type == StructureType::QUEUE || type == StructureType::LIST) {
                    DrawLine(node.position.x + 35, node.position.y,
                             node.position.x + spacing - 35, node.position.y, DARKGRAY);

                    DrawTriangle(
                        Vector2{node.position.x + spacing - 35, node.position.y - 5},
                        Vector2{node.position.x + spacing - 35, node.position.y + 5},
                        Vector2{node.position.x + spacing - 25, node.position.y},
                        DARKGRAY
                    );
                }
                else if (type == StructureType::STACK) {
                    DrawLine(node.position.x, node.position.y - 35,
                             node.position.x, node.position.y - spacing + 35, DARKGRAY);

                    DrawTriangle(
                        Vector2{node.position.x - 5, node.position.y - spacing + 35},
                        Vector2{node.position.x + 5, node.position.y - spacing + 35},
                        Vector2{node.position.x, node.position.y - spacing + 25},
                        DARKGRAY
                    );
                }
            }
            else if (type == StructureType::LIST) {
                DrawText("NULL", node.position.x + 60, node.position.y - 10, 20, DARKGRAY);
            }
        }

        // Draw animating (removed) nodes
        int animSize = animatingNodes.size();
        for (int i = 0; i < animSize; i++) {
            Node node = animatingNodes.getFront();
            animatingNodes.dequeue();

            Color fadeColor = ColorAlpha(node.color, node.alpha);
            DrawCircle(node.position.x, node.position.y, 30, fadeColor);

            std::string valueStr = std::to_string(node.value);
            DrawText(valueStr.c_str(),
                     node.position.x - MeasureText(valueStr.c_str(), 20) / 2,
                     node.position.y - 10,
                     20,
                     ColorAlpha(WHITE, node.alpha));

            animatingNodes.enqueue(node);
        }

        // Structure-specific info
        std::string sizeInfo = "Size: " + std::to_string(nodes.size());
        DrawText(sizeInfo.c_str(), 50, 800, 20, DARKGRAY);

        if (!nodes.empty()) {
            if (type == StructureType::QUEUE) {
                DrawText(("Front: " + std::to_string(nodes.front().value)).c_str(), 50, 820, 20, DARKGRAY);
                DrawText(("Rear: " + std::to_string(nodes.back().value)).c_str(), 50, 840, 20, DARKGRAY);
            }
            else if (type == StructureType::STACK) {
                DrawText(("Top: " + std::to_string(nodes.back().value)).c_str(), 50, 820, 20, DARKGRAY);
            }
            else if (type == StructureType::LIST) {
                DrawText(("Head: " + std::to_string(nodes.front().value)).c_str(), 50, 820, 20, DARKGRAY);
                DrawText(("Tail: " + std::to_string(nodes.back().value)).c_str(), 50, 840, 20, DARKGRAY);
            }
        }
    }
};
