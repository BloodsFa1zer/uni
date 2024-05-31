// Block 1: 2, 3, 5
// Block 2: 7, 11
// Block 3: 13, 15
// Block 4: 18
// Block 5: 21
// Block 6: 22


#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <unordered_map>
#include <string>
#include <cctype>
#include <stack>
#include <cmath>

using namespace std;
using namespace chrono;

void loadingAnimation() {
    for (int i = 0; i < 3; ++i) {
        cout << "Loading.";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";

        cout << "Loading..";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";

        cout << "Loading...";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";
    }
}

int getIntInput(const string& prompt, int minValue, int maxValue) {
    int value;
    bool inputIsValid;
    do {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            inputIsValid = true;
        } else {
            cerr << "\n### Invalid input. Please enter a valid integer between "
                 << minValue << " and " << maxValue << ". ###\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputIsValid = false;
        }
    } while (!inputIsValid);
    return value;
}


// Block 0
struct Node {
    int data;
    vector<Node*> children;

    Node(int val) : data(val) {}
};

// Function to add a child node to the given parent node
void addChild(Node* parent, int value) {
    parent->children.push_back(new Node(value));
}



// Block 1
// Function to get the node at a specified path
Node* getNodeByPath(Node* root, const vector<int>& path) {
    Node* current = root;
    for (int index : path) {
        if (index < 0 || index >= current->children.size()) {
            return nullptr;
        }
        current = current->children[index];
    }
    return current;
}

// Function to get the path to a specified node
vector<int> getPathToNode(Node* root, Node* target) {
    vector<int> path;
    if (root == nullptr || target == nullptr) return path;

    if (root == target) return path; // No need to traverse if root is the target

    vector<Node*> stack;
    vector<vector<int>> paths;
    stack.push_back(root);
    vector<int> currentPath;
    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();

        // Add the current node to the path
        currentPath.push_back(current->data);

        if (current == target) {
            path = currentPath;
            break;
        }

        for (int i = current->children.size() - 1; i >= 0; --i) {
            stack.push_back(current->children[i]);
        }

        while (!currentPath.empty() && stack.back()->data != currentPath.back()) {
            currentPath.pop_back();
        }
    }

    return path;
}

void addNodeByPath(Node* root, const vector<int>& path, int value) {
    // Find the parent node
    Node* parent = getNodeByPath(root, path);
    if (parent == nullptr) {
        cerr << "Parent node not found at the specified path" << endl;
        return;
    }

    // Add the new node as a child to the parent node
    parent->children.push_back(new Node(value));
}

int countChildren(Node* node) {
    return node->children.size();
}

// Function to calculate the height of a subtree rooted at the given node
int subtreeHeight(Node* node) {
    if (node == nullptr) return 0;

    int maxHeight = 0;
    for (Node* child : node->children) {
        int childHeight = subtreeHeight(child);
        maxHeight = max(maxHeight, childHeight);
    }
    return maxHeight + 1;
}

// Function to calculate the size of a subtree rooted at the given node
int subtreeSize(Node* node) {
    if (node == nullptr) return 0;

    int size = 1;
    for (Node* child : node->children) {
        size += subtreeSize(child);
    }
    return size;
}

// Function to calculate the average number of children, height, and size of non-leaf nodes
void calculateAverages(Node* root, double& avgChildren, double& avgHeight, double& avgSize, int& countNonLeafNodes) {
    avgChildren = 0.0;
    avgHeight = 0.0;
    avgSize = 0.0;
    countNonLeafNodes = 0;

    vector<Node*> stack;
    stack.push_back(root);
    while (!stack.empty()) {
        Node* current = stack.back();
        stack.pop_back();

        if (!current->children.empty()) {
            avgChildren += countChildren(current);
            avgHeight += subtreeHeight(current);
            avgSize += subtreeSize(current);
            countNonLeafNodes++;
        }

        for (Node* child : current->children) {
            stack.push_back(child);
        }
    }

    if (countNonLeafNodes > 0) {
        avgChildren /= countNonLeafNodes;
        avgHeight /= countNonLeafNodes;
        avgSize /= countNonLeafNodes;
    }
}



// Block 2
// Function to print the tree with paths
void printTreeWithPath(Node* root, const string& path = "") {
    if (root == nullptr) return;

    string nodePath = path + to_string(root->data) + " -> ";

    cout << nodePath << root->data << endl;

    for (Node* child : root->children) {
        printTreeWithPath(child, nodePath);
    }
}

// Function to print the path to a node with equal spacing
void printPathWithEqualSpacing(Node* root, const vector<int>& path) {
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << " : " << root->data << endl;
}

// Function to perform depth-first traversal and print paths with equal spacing
void printTreeWithEqualSpacing(Node* root, vector<int>& path) {
    if (root == nullptr) {
        return;
    }

    printPathWithEqualSpacing(root, path);

    // Traverse children
    for (Node* child : root->children) {
        path.push_back(child->data);
        printTreeWithEqualSpacing(child, path);
        path.pop_back();
    }
}



// Block 3
// Function to remove a node from the tree and return its subtree
Node* removeNodeByPath(Node* root, const vector<int>& path) {
    if (root == nullptr) return nullptr;

    vector<int> parentPath(path.begin(), path.end() - 1);
    Node* parent = getNodeByPath(root, parentPath);
    if (parent == nullptr) {
        cerr << "Parent node not found at the specified path" << endl;
        return nullptr;
    }

    // Extract the index of the node to be removed
    int indexToRemove = path.back();

    if (indexToRemove < 0 || indexToRemove >= parent->children.size()) {
        cerr << "Invalid index for child node" << endl;
        return nullptr;
    }
    Node* removedNode = parent->children[indexToRemove];
    parent->children.erase(parent->children.begin() + indexToRemove);

    // Return the removed subtree
    return removedNode;
}

// Function to delete a node and free memory
void deleteNode(Node* node) {
    if (node == nullptr) return;

    for (Node* child : node->children) {
        deleteNode(child);
    }

    delete node;
}

// Function to remove nodes with a specific value from the tree
void removeNodesByValue(Node* root, int value) {
    if (root == nullptr) return;

    if (root->data == value) {
        deleteNode(root);
        return;
    }

    for (auto it = root->children.begin(); it != root->children.end();) {
        if ((*it)->data == value) {
            // Delete the node and free memory
            deleteNode(*it);
            it = root->children.erase(it);
        } else {
            removeNodesByValue(*it, value);
            ++it;
        }
    }
}


// Block 4
struct BinaryTreeNode {
    int data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to insert a new node with a given value into a binary search tree
BinaryTreeNode* insertNode(BinaryTreeNode* root, int value) {
    // If the tree is empty, create a new node and make it the root
    if (root == nullptr) {
        return new BinaryTreeNode(value);
    }

    // If the value is less than the current node's value, go left
    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
        // If the value is greater than or equal to the current node's value, go right
    else {
        root->right = insertNode(root->right, value);
    }

    return root;
}

// Block 4.2
// Function to print the binary tree with brackets for children
void printBinaryTreeWithBrackets(BinaryTreeNode* root) {
    if (root == nullptr) return;

    cout << root->data;

    // Print left child if exists
    if (root->left != nullptr || root->right != nullptr) {
        cout << " (";
        printBinaryTreeWithBrackets(root->left);
        cout << ", ";
        printBinaryTreeWithBrackets(root->right);
        cout << ")";
    }
}

// Function to print the binary tree with paths
void printBinaryTreeWithPath(BinaryTreeNode* root, const string& path = "") {
    if (root == nullptr) return;

    // Construct the path for the current node
    string nodePath = path + to_string(root->data) + " -> ";

    cout << nodePath << root->data << endl;

    printBinaryTreeWithPath(root->left, nodePath);
    printBinaryTreeWithPath(root->right, nodePath);
}

//Block 5
// Function to print the binary tree in pre-order traversal
void printPreorder(BinaryTreeNode* root) {
    if (root == nullptr) return;

    cout << root->data << " ";

    // Recursively print the left subtree
    printPreorder(root->left);

    // Recursively print the right subtree
    printPreorder(root->right);
}



// Block 6
// Node structure for arithmetic expression tree
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to check if a given string represents an operator
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

// Function to check if a given string represents a variable
bool isVariable(const string& token) {
    return isalpha(token[0]);
}

// Function to check if a given string represents a numeric constant
bool isNumeric(const string& token) {
    for (char c : token) {
        if (!isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

// Function to evaluate an arithmetic expression tree
double evaluate(TreeNode* root, const unordered_map<string, double>& variables) {
    if (root == nullptr) return 0.0;

    if (!isOperator(root->value)) {
        // If the node is an operand (variable or constant), return its value
        if (isdigit(root->value[0]) || root->value[0] == '-') {
            return stod(root->value);
        } else {
            // If the node is a variable, look up its value in the variables map
            auto it = variables.find(root->value);
            if (it != variables.end()) {
                return it->second;
            } else {
                cerr << "Error: Undefined variable '" << root->value << "'" << endl;
                return 0.0;
            }
        }
    }

    double leftValue = evaluate(root->left, variables);
    double rightValue = evaluate(root->right, variables);

    if (root->value == "+") {
        return leftValue + rightValue;
    } else if (root->value == "-") {
        return leftValue - rightValue;
    } else if (root->value == "*") {
        return leftValue * rightValue;
    } else if (root->value == "/") {
        if (rightValue == 0) {
            cerr << "Error: Division by zero" << endl;
            return 0.0;
        }
        return leftValue / rightValue;
    } else if (root->value == "^") {
        return pow(leftValue, rightValue);
    }

    cerr << "Error: Unknown operator '" << root->value << "'" << endl;
    return 0.0;
}

// Function to simplify an arithmetic expression tree
TreeNode* simplify(TreeNode* root, const unordered_map<string, double>& variables) {
    if (root == nullptr) return nullptr;

    // If the node is an operand or variable, return it as is
    if (!isOperator(root->value)) {
        // If the node is a variable, look up its value in the variables map
        if (variables.find(root->value) != variables.end()) {
            return new TreeNode(to_string(variables.at(root->value)));
        } else {
            return new TreeNode(root->value);
        }
    }

    TreeNode* left = simplify(root->left, variables);
    TreeNode* right = simplify(root->right, variables);

    // If both subtrees are operands, evaluate the expression
    if (!isOperator(left->value) && !isOperator(right->value)) {
        double result = evaluate(root, variables);
        return new TreeNode(to_string(result));
    }

    root->left = left;
    root->right = right;
    return root;
}

TreeNode* constructExpressionTree(const string& expression) {
    stack<TreeNode*> nodeStack;

    for (char current : expression) {
        // If current character is a whitespace, skip it
        if (isspace(current)) {
            continue;
        }

        // If current character is an operand (variable or constant)
        if (isalnum(current)) {
            nodeStack.push(new TreeNode(string(1, current)));
        }
            // If current character is an operator
        else {
            TreeNode* rightOperand = nodeStack.top();
            nodeStack.pop();
            TreeNode* leftOperand = nodeStack.top();
            nodeStack.pop();

            TreeNode* operatorNode = new TreeNode(string(1, current));
            operatorNode->left = leftOperand;
            operatorNode->right = rightOperand;

            nodeStack.push(operatorNode);
        }
    }

    return nodeStack.top();
}

// Function to print the arithmetic expression tree in infix notation
void printInfix(TreeNode* root, bool isRoot = true) {
    if (root == nullptr) return;


    if (!isRoot && isOperator(root->value)) {
        cout << "(";
    }

    // Print left subtree
    printInfix(root->left, false);

    cout << root->value;

    // Print right subtree
    printInfix(root->right, false);

    if (!isRoot && isOperator(root->value)) {
        cout << ")";
    }
}



void userManagementMode();
void demonstrationMode();

int main() {
    srand(time(nullptr));
    int mode;
    mode = getIntInput("Select mode:\n"
                       "1. User management mode\n"
                       "2. Demonstration mode \n", 1, 2);

    switch (mode) {
        case 1:
            userManagementMode();
            break;
        case 2:
            demonstrationMode();
            break;
    }

    return 0;
}

void userManagementMode() {
    int option, mode = 0;

    mode = getIntInput("Select mode:\n"
                       "1.Tree\n"
                       "2.Binary Tree\n"
                       "3.Expression Tree\n"
                       "0. Exit", 0, 3);
    switch (mode) {
        case 0: {
            cout << "Thanks for using system" << endl;
            return;
        }
        case 1: {
            Node *root = new Node(1);
            root->children.push_back(new Node(2));
            root->children.push_back(new Node(3));
            root->children[0]->children.push_back(new Node(4));
            root->children[0]->children.push_back(new Node(5));
            root->children[1]->children.push_back(new Node(6));
            do {
                option = getIntInput("Select option:\n"
                                     "1. Find Node by Path\n"
                                     "2. Get Path to Node\n"
                                     "3. Add Node by Path\n"
                                     "4. Calculate Averages\n"
                                     "5. Print Tree with Path\n"
                                     "6. Print Path with Equal Spacing\n"
                                     "7. Print Tree with Equal Spacing\n"
                                     "8. Remove Node by Path\n"
                                     "9. Remove Nodes by Value\n"
                                     "10. Clean up Memory\n"
                                     "0. Exit", 0, 10);
                switch (option) {
                    case 0: {
                        cout << "Thanks for using system" << endl;
                        return;
                    }
                    case 1: {
                        vector<int> pathToNode;
                        cout << "Enter path to node (space-separated integers): ";
                        int index;
                        while (cin >> index) {
                            pathToNode.push_back(index);
                        }
                        Node *node = getNodeByPath(root, pathToNode);
                        if (node) {
                            cout << "Node found: " << node->data << endl;
                        } else {
                            cout << "Node not found" << endl;
                        }
                        break;
                    }
                    case 2: {
                        int targetNodeData;
                        cout << "Enter data of target node: ";
                        cin >> targetNodeData;
                        Node *targetNode = new Node(targetNodeData);
                        vector<int> path = getPathToNode(root, targetNode);
                        if (!path.empty()) {
                            cout << "Path to node: ";
                            for (int index: path) {
                                cout << index << " ";
                            }
                            cout << endl;
                        } else {
                            cout << "Node not found" << endl;
                        }
                        delete targetNode;
                        break;
                    }
                    case 3: {
                        vector<int> parentPath;
                        int value;
                        cout << "Enter parent path (space-separated integers): ";
                        int index;
                        while (cin >> index) {
                            parentPath.push_back(index);
                        }
                        cout << "Enter value for new node: ";
                        cin >> value;
                        addNodeByPath(root, parentPath, value);
                        break;
                    }
                    case 4: {
                        double avgChildren, avgHeight, avgSize;
                        int countNonLeafNodes;
                        calculateAverages(root, avgChildren, avgHeight, avgSize, countNonLeafNodes);
                        cout << "Average Number of Children: " << avgChildren << endl;
                        cout << "Average Height: " << avgHeight << endl;
                        cout << "Average Size: " << avgSize << endl;
                        cout << "Count of Non-Leaf Nodes: " << countNonLeafNodes << endl;
                        break;
                    }
                    case 5: {
                        cout << "Tree with Paths:\n";
                        printTreeWithPath(root);
                        break;
                    }
                    case 6: {
                        cout << "Printing Paths with Equal Spacing:\n";
                        vector<int> path; // Initialize an empty path
                        printTreeWithEqualSpacing(root, path);
                        break;
                    }
                    case 7: {
                        cout << "Printing Tree with Equal Spacing:\n";
                        vector<int> path; // Initialize an empty path
                        printTreeWithEqualSpacing(root, path);
                        break;
                    }
                    case 8: {
                        vector<int> pathToRemove;
                        cout << "Enter the path to the node you want to remove (separated by spaces): ";
                        int value;
                        while (cin >> value) {
                            pathToRemove.push_back(value);
                        }
                        Node *removedNode = removeNodeByPath(root, pathToRemove);
                        if (removedNode != nullptr) {
                            cout << "Node with value " << removedNode->data << " removed successfully.\n";
                        }
                        break;
                    }
                    case 9: {
                        int valueToRemove;
                        cout << "Enter the value of the node you want to remove: ";
                        cin >> valueToRemove;
                        removeNodesByValue(root, valueToRemove);
                        cout << "Nodes with value " << valueToRemove << " removed successfully.\n";
                        break;
                    }
                    case 10: {
                        deleteNode(root);
                        cout << "Memory cleaned up successfully.\n";
                        root = nullptr;
                        break;
                    }

                }
            } while (true);
            break;
        }
        case 2: {
            BinaryTreeNode* root = nullptr;
            do {
                option = getIntInput("Select option:\n"
                                     "1. Insert Node\n"
                                     "2. Print Tree with Brackets\n"
                                     "3. Print Tree with Paths\n"
                                     "4. Print Preorder Traversal\n"
                                     "0. Exit", 0, 4);
                switch (option) {
                    case 0: {
                        cout << "Thanks for using system" << endl;
                        return;
                    }
                    case 1: {
                        int value;
                        cout << "Enter the value to insert: ";
                        cin >> value;
                        root = insertNode(root, value);
                        cout << "Node with value " << value << " inserted successfully.\n";
                        break;
                    }
                    case 2: {
                        cout << "Binary Tree with Brackets:\n";
                        printBinaryTreeWithBrackets(root);
                        cout << endl;
                        break;
                    }
                    case 3: {
                        cout << "Binary Tree with Paths:\n";
                        printBinaryTreeWithPath(root);
                        cout << endl;
                        break;
                    }
                    case 4: {
                        cout << "Preorder Traversal: ";
                        printPreorder(root);
                        cout << endl;
                        break;
                    }
                }
            }while (true);
            break;
        }
        case 3: {
            TreeNode* ExprRoot = nullptr;
            do {
                option = getIntInput("Select option:\n"
                                     "1. Create Expression Tree\n"
                                     "2. Print Infix Expression\n"
                                     "3. Take already created expression\n"
                                     "0. Exit", 0, 2);
                cin.ignore();
                switch (option) {
                    case 0: {
                        cout << "Thanks for using system" << endl;
                        return;
                    }
                    case 1: {
                        cout << "Enter an expression tree in postfix notation: ";
                        string expression;
                        getline(cin, expression);
                        TreeNode* root = constructExpressionTree(expression);

                        cout << "Expression tree created successfully!" << endl;
                        break;
                    }
                    case 2: {
                        if (ExprRoot != nullptr) {
                            cout << "Infix Expression: ";
                            printInfix(ExprRoot);
                            cout << endl;
                        } else {
                            cout << "Expression tree is not created yet!" << endl;
                        }

                        break;
                    }
                    case 3: {
                        TreeNode* ExpressionRoot = new TreeNode("+");
                        ExpressionRoot->left = new TreeNode("*");
                        ExpressionRoot->left->left = new TreeNode("x");
                        ExpressionRoot->left->right = new TreeNode("5");
                        ExpressionRoot->right = new TreeNode("/");
                        ExpressionRoot->right->left = new TreeNode("10");
                        ExpressionRoot->right->right = new TreeNode("2");

                        unordered_map<string, double> variables = {{"x", 3.0}};

                        break;
                    }
                }
            } while (true);
            break;
        }
    }

}

void demonstrationMode() {

    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ Creating a tree and adding nodes @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();

    Node* root = new Node(1);
    root->children.push_back(new Node(2));
    root->children.push_back(new Node(3));
    root->children[0]->children.push_back(new Node(4));
    root->children[0]->children.push_back(new Node(5));
    root->children[1]->children.push_back(new Node(6));
    root->children[1]->children.push_back(new Node(7));
    Node* rootTmp = root;
    printTreeWithPath(rootTmp);


    // Demonstrate getNodeByPath function
    cout << "\n\n@@@@@ Finding the node with path {0, 1} in the tree. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    vector<int> pathToNode = {0, 1}; // Path to node 5
    Node* node = getNodeByPath(root, pathToNode);
    if (node) {
        cout << "Node found: " << node->data << endl;
    } else {
        cout << "Node not found" << endl;
    }

    // Demonstrate getPathToNode function
    cout << "\n\n@@@@@ Finding the path to node 6 from the root node in the tree @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    Node* targetNode = root->children[1]->children[0]; // Target node - 6
    vector<int> path = getPathToNode(root, targetNode);
    if (!path.empty()) {
        cout << "Path to node: ";
        for (int index : path) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Node not found" << endl;
    }

    // Demonstrate addNodeByPath function
    cout << "\n\n@@@@@ Adding a new node with the value 7 as a child to node 2(new child) in the tree. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    vector<int> parentPath = {0};
    addNodeByPath(root, parentPath, 8);


    // Print the tree nodes along with their paths
    cout << "\n\n@@@@@ Printing the tree nodes along with their paths @@@@@\n\n" << endl;
    loadingAnimation();
    rootTmp = root;
    printTreeWithPath(rootTmp);


    cout << "\n\n@@@@@ Printing the tree nodes with equal spacing, including the path to each node @@@@@\n\n" << endl;
    loadingAnimation();
    vector<int> Path;
    rootTmp = root;
    path.push_back(rootTmp->data);
    printTreeWithEqualSpacing(rootTmp, path);



    cout << "\n\n@@@@@ Removing a node from the tree using the path {1, 0} @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    vector<int> pathToRemove = {1, 0};
    Node* removedNode = removeNodeByPath(root, pathToRemove);
    if (removedNode != nullptr) {
        cout << "Removed node value: " << removedNode->data << endl;
    }
    rootTmp = root;
    printTreeWithPath(rootTmp);

    // Remove nodes with a specific value
    cout << "\n\n@@@@@ Removing all nodes with the value 3 from the tree. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    removeNodesByValue(root, 3);

    // Print the modified tree
    rootTmp = root;
    loadingAnimation();
    cout << "Tree after removal:" << endl;
    printTreeWithPath(rootTmp);

    // Cleanup memory
    cout << "\n\n@@@@@ Cleaning up the memory by deleting the entire tree rooted at root @@@@@\n\n" << endl;
    loadingAnimation();
    deleteNode(root);


    cout << "\n\n@@@@@ Inserting nodes with random values into a binary search tree. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    BinaryTreeNode* BinaryRoot = nullptr;

    // Insert nodes into the binary search tree
    BinaryRoot = insertNode(BinaryRoot, 5);
    insertNode(BinaryRoot, 3);
    insertNode(BinaryRoot, 7);
    insertNode(BinaryRoot, 2);
    insertNode(BinaryRoot, 4);
    insertNode(BinaryRoot, 6);
    insertNode(BinaryRoot, 8);


    // Print the binary tree with brackets
    cout << "\n\n@@@@@ Printing the binary tree with brackets @@@@@\n\n" << endl;
    loadingAnimation();
    cout << "Binary Tree with Brackets:" << endl;
    printBinaryTreeWithBrackets(BinaryRoot);
    cout << endl;

    // Print the binary tree with paths
    cout << "\n\n@@@@@ Printing the binary tree with paths. @@@@@\n\n" << endl;
    loadingAnimation();
    cout << "Binary Tree with Paths:" << endl;
    printBinaryTreeWithPath(BinaryRoot);
    cout << endl;

    // Print the binary tree in preorder traversal
    cout << "\n\n@@@@@ Printing the binary tree in preorder traversal. @@@@@\n\n" << endl;
    loadingAnimation();
    cout << "Preorder Traversal: ";
    printPreorder(BinaryRoot);
    cout << endl;



    // Construct an arithmetic expression tree
    cout << "\n\n@@@@@ Constructing an arithmetic expression tree representing the expression 'x * 5 + 10 / 2' @@@@@\n\n\n";
    loadingAnimation();
    loadingAnimation();
    TreeNode* ExpressionRoot = new TreeNode("+");
    ExpressionRoot->left = new TreeNode("*");
    ExpressionRoot->left->left = new TreeNode("x");
    ExpressionRoot->left->right = new TreeNode("5");
    ExpressionRoot->right = new TreeNode("/");
    ExpressionRoot->right->left = new TreeNode("10");
    ExpressionRoot->right->right = new TreeNode("2");

    // Assign the value of 'x' before evaluation
    unordered_map<string, double> variables = {{"x", 3.0}};

    // Print the expression tree in infix notation
    cout << "\n\n@@@@@ Printing the infix expression represented by the arithmetic expression tree with x = 3. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();
    cout << "Infix Expression: ";
    printInfix(ExpressionRoot);
    cout << endl;

    // Simplify the expression tree
    cout << "\n\n@@@@@ Simplifying the arithmetic expression tree. @@@@@\n\n" << endl;
    loadingAnimation();
    loadingAnimation();

    // Simplify the expression tree
    TreeNode* simplified = simplify(ExpressionRoot, variables);

    // Print the simplified expression
    cout << "Simplified Infix Expression: ";
    printInfix(simplified);
    cout << endl;

    cout << "\n**** THANKS FOR USING *****\n";
}
