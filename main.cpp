#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <cassert>

class Node {
public:
    std::string value;
    Node* right = nullptr;
    Node* left = nullptr;

    Node(std::string _value) : value(_value), right(nullptr), left(nullptr) {}
};

class AvlNode {
public:
    std::string value;
    int height;
    AvlNode* right;
    AvlNode* left;

    AvlNode(std::string v) : value(v), right(nullptr), left(nullptr), height(0) {}
};

class BTS {
    Node* root;

    Node* insert(Node* prt, std::string v) {
        if (prt == nullptr) {
            return new Node(v);
        }

        if (v > prt->value) {
            prt->right = insert(prt->right, v);
        } else {
            prt->left = insert(prt->left, v);
        }

        return prt;
    }

    bool Search(Node* Proot, std::string s_data) {
        if (Proot == nullptr) {
           // std::cout << "Tree is empty" << std::endl;
            return false;
        } else if (Proot->value == s_data) {
           // std::cout << "Found" << std::endl;
            return true;
        } else if (Proot->value < s_data)
            return Search(Proot->right, s_data);
        else
            return Search(Proot->left, s_data);
    }

    void clear(Node*& Proot) {
        if (Proot != nullptr) {
            clear(Proot->left);
            clear(Proot->right);
            delete Proot;
            Proot = nullptr;
        }
    }

public:
    BTS() : root(nullptr) {}

    Node* getRoot() {
        return root;
    }

    bool search(std::string value) {
        return Search(root, value);
    }

    void clear() {
        clear(root);
    }

    void Insert(std::string v) {
        root = insert(root, v);
    }
};

class AVLTree {
private:
    AvlNode* root;

    AvlNode* insertAVL(AvlNode* node, const std::string& data) {
        if (node == nullptr) {
            return new AvlNode(data);
        }

        if (data < node->value)
            node->left = insertAVL(node->left, data);
        else if (data > node->value)
            node->right = insertAVL(node->right, data);

        node->height = 1 + std::max(height(node->right), height(node->left));

        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }


        if (balance < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    int height(AvlNode* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(AvlNode* node) {
        return (node == nullptr) ? 0 : height(node->left) - height(node->right);
    }

    AvlNode* rotateLeft(AvlNode* node) {
        AvlNode* newParent = node->right;
        node->right = newParent->left;
        newParent->left = node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        newParent->height = 1 + std::max(height(newParent->left), height(newParent->right));

        return newParent;
    }

    AvlNode* rotateRight(AvlNode* node) {
        AvlNode* newParent = node->left;
        node->left = newParent->right;
        newParent->right = node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        newParent->height = 1 + std::max(height(newParent->left), height(newParent->right));

        return newParent;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const std::string& data) {
        root = insertAVL(root, data);
    }

    bool search(const std::string& data) {
        AvlNode* current = root;
        while (current != nullptr) {
            if (data == current->value) {
                return true;
            } else if (data < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void clear() {
        clear(root);
    }

    ~AVLTree() {
        clear();
    }

private:
    void clear(AvlNode*& node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }

    }
};

int main() {
    std::ifstream file_in("dictionary.txt");
    //assert(file_in.is_open());
    std::ofstream insert_file_out;
    std::ofstream search_file_out;
    int step = 100;
    int numberOfWords = 10000;

    using ns = std::chrono::nanoseconds;
    using clock = std::chrono::steady_clock;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, numberOfWords - 1);

    std::vector<std::string> words(numberOfWords);

    for (int i = 0; i < words.size(); ++i) {

        file_in >> words[i];
        //std::cout<<words[i]<<std::endl;
    }
    file_in.close();



    std::vector<ns> avl_insert_times(numberOfWords / step, ns(0));
    std::vector<ns> avl_search_times(numberOfWords / step, ns(0));
    std::vector<ns> bst_insert_times(numberOfWords / step, ns(0));
    std::vector<ns> bst_search_times(numberOfWords / step, ns(0));

    insert_file_out.open("randomIns.txt");
    search_file_out.open("randomSearch.txt");

    for(int i =0; i < words.size(); i++)
    {
        swap(words[dist(gen)], words[dist(gen)]);

    }


    for (int times = 0; times < 1; ++times) {

        AVLTree avl_iteration;
        BTS bst_iteration;

        for (int i = 0; i < words.size(); ++i) {



                auto start = clock::now();
                avl_iteration.insert(words[i]);
                //std::cout << "inserted" << std::endl;
                auto end = clock::now();
                ns time_taken = std::chrono::duration_cast<ns>(end - start);
                avl_insert_times[i / step] += time_taken;

                // AVL search
                start = clock::now();
                avl_iteration.search(words[i]);
                //std::cout << "found AVL" << std::endl;
                end = clock::now();
                time_taken = std::chrono::duration_cast<ns>(end - start);
                avl_search_times[i / step] += time_taken;

                // BTS insert
                start = clock::now();
                bst_iteration.Insert(words[i]);
                //std::cout << "Inserted Binary" << std::endl;
                end = clock::now();
                time_taken = std::chrono::duration_cast<ns>(end - start);
                bst_insert_times[i / step] += time_taken;

                // BTS search
                start = clock::now();
                bst_iteration.search(words[i]);
                //std::cout << "Found BInary" << std::endl;
                end = clock::now();
                //count++;
                //std::cout << count << std::endl;
                time_taken = std::chrono::duration_cast<ns>(end - start);
                bst_search_times[i / step] += time_taken;



        }

    }
    insert_file_out<<"Size  BST   AVL"<<std::endl;
    for (int i = 0; i < bst_insert_times.size(); ++i)
    {
        insert_file_out << 100 * (i+1) << ' ' << bst_insert_times[i].count()<< ' ' << avl_insert_times[i].count()  << std::endl;
    }

    search_file_out<<"Size  BST   AVL"<<std::endl;
    for (int i = 0; i < bst_search_times.size(); ++i)
    {
        search_file_out << 100 * (i + 1) << ' ' << bst_search_times[i].count()  << ' ' << avl_search_times[i].count()<< std::endl;
    }

    insert_file_out.close();
    search_file_out.close();
    return 0;
}