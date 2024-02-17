#include <iostream>
#include <queue>
#include <vector>

class HuffmanNode {
public:
    char symbol;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char symbol, int frequency) : symbol(symbol), frequency(frequency), left(nullptr), right(nullptr) {}
};

class CompareNodes {
public:
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

class HuffmanTree {
public:
    HuffmanNode* buildTree(std::vector<char>& symbols, std::vector<int>& frequencies) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> nodeQueue;

        for (int i = 0; i < symbols.size(); i++) {
            nodeQueue.push(new HuffmanNode(symbols[i], frequencies[i]));
        }

        while (nodeQueue.size() > 1) {
            HuffmanNode* node1 = nodeQueue.top();
            nodeQueue.pop();
            HuffmanNode* node2 = nodeQueue.top();
            nodeQueue.pop();

            HuffmanNode* combined = new HuffmanNode('$', node1->frequency + node2->frequency);
            combined->left = node1;
            combined->right = node2;

            nodeQueue.push(combined);
        }

        return nodeQueue.top();
    }

    void printCodes(HuffmanNode* root, const std::string& prefix = "") {
        if (root == nullptr) {
            return;
        }

        if (root->symbol != '$') {
            std::cout << prefix << " ";
        }

        printCodes(root->left, prefix + "0");
        printCodes(root->right, prefix + "1");
    }
};

int main() {
    int numSymbols;
    std::cout << "Enter the number of symbols: ";
    std::cin >> numSymbols;

    std::vector<char> symbols(numSymbols);
    std::vector<int> frequencies(numSymbols);

    std::cout << "Enter the symbols and their frequencies:\n";
    for (int i = 0; i < numSymbols; i++) {
        std::cin >> symbols[i] >> frequencies[i];
    }

    HuffmanTree huffmanTree;
    HuffmanNode* root = huffmanTree.buildTree(symbols, frequencies);
    huffmanTree.printCodes(root);

    return 0;
}
