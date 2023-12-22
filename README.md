# AVL_BST_Trees
This programs written in C++
Comparison Between Binary Search and AVL Tree


# 1. Introduction:
In this work, we examine the following issue: Using AVL and BST trees as the data store, create a dictionary. Our goal is to examine and contrast the performance of BST and AVL trees.
Although there are many different techniques and operations that may be used with trees (particularly depending on the type and implementation methods), we will concentrate on insertion and searching in this examination.
# 1.1 Binary Search Tree:
Binary Search Trees (BST) facilitate rapid data lookup and addition through binary search, leveraging the arrangement of nodes to skip approximately half of the tree in each comparison. The performance of a binary search tree is influenced by the order in which nodes are inserted, as arbitrary insertions can lead to the degeneracy of the tree structure.
Upon complexity analysis, the average time for insert and search operations for n nodes is determined. In the worst case, searching for a specific key in a binary search tree can be implemented either recursively or iteratively.
In this analysis, iterative methods are employed for searching and clearing the tree in the case of BST, with the acknowledgment that the speed of these operations is not under consideration.
# Time Complexity:
•	In a balanced BST, the average time complexity for insertion, deletion, and search operations is O(log n), where n is the number of nodes.
•	However, if the tree becomes unbalanced (resembling a linked list), the time complexity can degrade to O(n), making self-balancing variants like AVL trees and Red-Black trees preferable in such cases.
# 1.2 AVL Tree:
AVL trees, named after their inventors Adelson-Velsky and Landis, are a self-balancing variant of Binary Search Trees (BST). In AVL trees, the balance factor of each node, defined as the height of the left subtree minus the height of the right subtree, is maintained to be in the range of {-1, 0, 1}. This ensures that the tree remains balanced, preventing it from degenerating into a linked list and maintaining an overall logarithmic height.

The time complexity of basic operations in AVL trees, including insertion, deletion, and search, is O(log n) on average, where n is the number of nodes in the tree. This logarithmic complexity is achieved due to the self-balancing nature of AVL trees, which guarantees a balanced structure even after successive insertions or deletions. While the overhead of AVL trees in terms of rotations during balancing can introduce additional constants, the overall benefit lies in maintaining efficient and predictable performance for essential operations.
# 2. Methodology:
	Both trees were implemented in C++ 17 programming language. We simulated the process of storing a dictionary by using a.txt file that included 10,000 English words arranged alphabetically. Three cases was tested: randomly, partly, and sorted data.

# 3.Result:
	As anticipated, when the data is sorted, Binary Search Tree (BST) exhibits significantly slower performance in both insertion and searching compared to AVL trees.(Graph1,Graph2) Even with partly sorted data, there is a marginal improvement, but AVL trees still outperform BST by a considerable margin(Graph 3, Graph 4). The situation becomes more intriguing with randomly ordered data: BST insertion is faster due to the likely imbalance, reducing the need for rotations. However, AVL trees maintain their speed advantage in insertion as no rotations are performed, and their expected lower height contributes to faster operations(Graph 5, Graph 6). In summary, AVL trees consistently demonstrate superior performance, especially in scenarios involving sorted or partly sorted data, while showcasing competitive efficiency in randomly ordered datasets.
