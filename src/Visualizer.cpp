//? cpp standard libraries
#include <iostream>
#include <cassert>
#include <vector>

//? installed libraries
#include <raylib.h>

//? Files
#include"../include/Node.hpp"
#include"../include/DataStructureType.hpp"

#include"../include/Queue.hpp"
#include"../include/Stack.hpp"
#include"../include/LinkedList.hpp"

// Constants
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 920;


// Data Structure Visualizer class
class DataStructureVisualizer {
private:
    std::vector<Node> nodes;
    Vector2 startPosition;
    float nodeSpacing;
    Queue<Node> animatingNodes;

    void UpdateNodePositions() {
        for (int i = 0; i < nodes.size(); i++) {
            Vector2 targetPos = {startPosition.x + i * nodeSpacing, startPosition.y};
            nodes[i].position = targetPos;
        }
    }

public:
    DataStructureVisualizer() :
        startPosition({100, 300}),
        nodeSpacing(80) {}

    void AddNode(int value) {
        Vector2 newPosition = startPosition;
        if (!nodes.empty()) {
            newPosition.x = nodes.back().position.x + nodeSpacing;
        }
        nodes.push_back(Node(value, newPosition));
        UpdateNodePositions();
    }

    void RemoveNode(DataStructureType type) {
        if (nodes.empty()) return;

        Node removedNode = (type == DataStructureType::STACK) ? nodes.back() : nodes.front();
        removedNode.color = RED;
        animatingNodes.enqueue(removedNode);

        if (type == DataStructureType::STACK)
            nodes.pop_back();
        else
            nodes.erase(nodes.begin());

        UpdateNodePositions();
    }

    void Clear() {
        nodes.clear();
        animatingNodes.clear();
    }

    void Update() {
        // Update animating nodes
        int index = 0;
        while (index < animatingNodes.size()) {
            Node node = animatingNodes.getFront();
            animatingNodes.dequeue();

            node.alpha -= 0.05f;
            node.position.y -= 2.0f;

            if (node.alpha > 0)
                animatingNodes.enqueue(node); // Re-enqueue the node if needed
            ++index;
        }
    }

    void Draw(DataStructureType type) {
        // Draw base line
        DrawLine(50, 350, SCREEN_WIDTH - 50, 350, LIGHTGRAY);

        // Draw nodes
        for (int i = 0; i < nodes.size(); i++) {
            const Node& node = nodes[i];

            // Draw node circle
            DrawCircle(node.position.x, node.position.y, 30, node.color);

            // Draw value
            std::string valueStr = std::to_string(node.value);
            DrawText(valueStr.c_str(),
                    node.position.x - MeasureText(valueStr.c_str(), 20)/2,
                    node.position.y - 10,
                    20,
                    WHITE);

            // Draw arrows based on data structure type
            if (i < nodes.size() - 1) {
                DrawLine(node.position.x + 35,
                        node.position.y,
                        node.position.x + nodeSpacing - 35,
                        node.position.y,
                        DARKGRAY);

                // Draw arrow direction based on structure type
                if (type == DataStructureType::QUEUE) {
                    DrawTriangle(
                        Vector2{node.position.x + nodeSpacing - 35, node.position.y - 5},
                        Vector2{node.position.x + nodeSpacing - 35, node.position.y + 5},
                        Vector2{node.position.x + nodeSpacing - 25, node.position.y},
                        DARKGRAY
                    );
                } else if (type == DataStructureType::STACK) {
                    DrawTriangle(
                        Vector2{node.position.x + nodeSpacing - 25, node.position.y - 5},
                        Vector2{node.position.x + nodeSpacing - 25, node.position.y + 5},
                        Vector2{node.position.x + nodeSpacing - 35, node.position.y},
                        DARKGRAY
                    );
                }
            }
        }

        // Draw animating nodes
        int index = 0;
        while (index < animatingNodes.size()) {
            Node node = animatingNodes.getFront();
            animatingNodes.dequeue();

            Color fadeColor = ColorAlpha(node.color, node.alpha);
            DrawCircle(node.position.x,
                       node.position.y,
                       30,
                       fadeColor);

            std::string valueStr = std::to_string(node.value);
            DrawText(valueStr.c_str(),
                     node.position.x - MeasureText(valueStr.c_str(), 20) / 2,
                     node.position.y - 10,
                     20,
                     ColorAlpha(WHITE, node.alpha));

            animatingNodes.enqueue(node); // Re-enqueue the node if needed
            ++index;
        }

        // Draw structure-specific information
        std::string sizeInfo = "Size: " + std::to_string(nodes.size());
        DrawText(sizeInfo.c_str(), 50, 400, 20, DARKGRAY);

        if (!nodes.empty()) {
            std::string frontInfo;
            if (type == DataStructureType::QUEUE)
                frontInfo = "Front: " + std::to_string(nodes.front().value);
            else if (type == DataStructureType::STACK)
                frontInfo = "Top: " + std::to_string(nodes.back().value);
            DrawText(frontInfo.c_str(), 50, 430, 20, DARKGRAY);
        }
    }
};