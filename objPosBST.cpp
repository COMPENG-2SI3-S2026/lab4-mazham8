#include "objPosBST.h"

#include <iostream>
using namespace std;

objPosBST::objPosBST()
{
    // Constructor (Check Lecture Notes for Implementation, Simple)

    // Creates an empty binary search tree.
    // The root pointer does not reference a node initially.

    root = nullptr;    
}

objPosBST::~objPosBST()
{
    // Destructor
    // Invoke delete tree, then set root to NULL

    // Releases every dynamically allocated node in the tree.
    // The public deletion method restores the empty-tree invariant.

    deleteTree();
    root = nullptr;
}

void objPosBST::deleteTree(const TNode* thisNode)
{
	// Delete all nodes in the tree

    // Question from Class - Which Traversal Order should you use for this method?
    //   WARNING - using the wrong one will result in potential heap error.

    // Deletes every node in the subtree using post-order traversal.
    // Child nodes are deleted before their parent node.

    if(thisNode == nullptr) // if empty tree, just return
        return;

    deleteTree(thisNode->left); // left -> right -> parent
    deleteTree(thisNode->right);
    delete thisNode;
}

// Public Interface, Implemented
void objPosBST::deleteTree()
{
    deleteTree(root); // recursive call on the private helper function
    root = nullptr;
}

bool objPosBST::isEmptyTree() const
{
    // Check if tree is empty
    //  Really simple, think about how.

    // Determines whether the BST currently contains no nodes.
    // An empty tree is represented by a null root pointer.

    return root == nullptr;
}


bool objPosBST::isLeaf(const objPos &thisPos, const TNode* thisNode) const
{
    // Check if thisPos in a Leaf Node.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, check if the node is a leaf node

    // Remember, leaf nodes do not have children nodes

    // Searches by prefix and checks whether the matching node is a leaf.
    // A missing prefix returns false; a leaf has no child nodes.

    if(thisNode == nullptr)
        return false;

    if(thisPos.getPF() < thisNode->data.getPF())
        return isLeaf(thisPos, thisNode->left);

    if(thisPos.getPF() > thisNode->data.getPF())
        return isLeaf(thisPos, thisNode->right);

    return thisNode->left == nullptr && thisNode->right == nullptr;
}

bool objPosBST::isLeaf(const objPos &thisPos) const
{
    return isLeaf(thisPos, root);
}


void objPosBST::printTree(const TNode* thisNode) const  // private recursive
{
    // Print the entire tree content using **In-Order Traversal**

    // print in the format of Prefix + Number
    // e.g.  N30 P25 etc.

    // DO NOT use printObjPos() as it will mess up the game display.

    // Prints the subtree using in-order traversal. left subtree -> parent -> right subtree
    // Prefix ordering makes the output ascending by prefix.

    if(thisNode == nullptr)
        return;

    printTree(thisNode->left);
    cout << thisNode->data.getPF() << thisNode->data.getNum() << " ";
    printTree(thisNode->right);
}

void objPosBST::printTree() const  // public interface
{    
    if(root == NULL)
    {
        cout << "[Empty]";
        return;
    }
    printTree(root);
}


int objPosBST::getHeight(const TNode* thisNode) const
{
    // Tree Height Calculation Algorithm 

    // 1. If thisNode is null, height is zero.

    // 2. Otherwise, recursively invoke getHeight for the left and right subtree, and save
    //    the returned heights.

    // 3. Compare the two returned heights, and return the larger one.
}

void objPosBST::printCurrentLevel(const TNode* thisNode, const int level) const
{
    // Recursive Level-Order Tree-Printing Algorithm 
    
    // 1. First check if at leaf node.  If yes, do not print anything

    // 2. Then, check if level is 1.  If yes, print the Prefix field only (specified in manual)

    // 3. Otherwise, invoke recursively printCurrentLevel for left subtree with one less level, then
    //                                                        right subtree with one less level
    //    "if I'm not at the level, keep on searching into the left and the right subtrees"

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

// Public Interface.
void objPosBST::printTreeLevel() const
{
    // Interface to the Recursive Version of Level-Order Tree-Printing Algorithm 

    // 1. Get the height of the tree
    // 2. For each level (bounded by height), invoke the recursive tree-printing algorithm.

    // You may add other character formatting features to make the tree more readable.
    // (you will be asked to demo this feature during the lab demo!!)
}

bool objPosBST::isInTree(const objPos& thisPos, const TNode* thisNode) const
{
    // Check if thisPos in in the tree.
    //  Remember, tree nodes are inserted using the Prefix member of objPos

    // Algorithm Suggestion:
    // 1. if the node is NULL, just return false
    // 2. Otherwise, compare Prefix of the data of the current node
    //    against the Prefix of thisPos
    //      - If not equal, follow the BST search rules
    //      - If equal, return true

    // Searches the BST recursively using the objPos prefix field.
    // Reaching a null subtree means the requested prefix is absent.

    // for every node target prefix < current prefix  → search left
    // target prefix > current prefix  → search right
    // target prefix == current prefix → found

    if(thisNode == nullptr)
        return false;

    if(thisPos.getPF() < thisNode->data.getPF())
        return isInTree(thisPos, thisNode->left);

    if(thisPos.getPF() > thisNode->data.getPF())
        return isInTree(thisPos, thisNode->right);

    return true;
}

// Public Interface, Implemented
bool objPosBST::isInTree(const objPos &thisPos) const
{
    return isInTree(thisPos, root); // recursive call on the private helper function
}

// insert OR update!!
void objPosBST::insert(const objPos &thisPos, TNode* &thisNode)
{
    // Insert objPos as a Node into the BST

    // Check Lecture Notes for general implementation
    //  Hint: Algorithm similar to isInTree.

    // Modification: 
    //   If the node is already in the tree (i.e. Prefix match found)
    //   Add the number member of thisPos to the number member of the objPos data at the node
    //   (DO NOT JUST IGNORE.  ADD NUMBERS!!)

        // Inserts a new node according to its prefix ordering.
    // A duplicate prefix adds its number to the existing node.

    if(thisNode == nullptr)
    {
        thisNode = new TNode(thisPos); // create a node at the empty subtree
        return;
    }

    if(thisPos.getPF() < thisNode->data.getPF())
    {
        insert(thisPos, thisNode->left);
    }
    else if(thisPos.getPF() > thisNode->data.getPF())
    {
        insert(thisPos, thisNode->right);
    }
    else
    {
        int updatedNumber = thisNode->data.getNum() + thisPos.getNum();
        thisNode->data.setNum(updatedNumber); // merge the duplicate-prefix score
    }
}

// Public Interface, Implemented
void objPosBST::insert(const objPos &thisPos)
{
    insert(thisPos, root); // recursive call on the private helper function
}


const TNode* objPosBST::findMin(const TNode* thisNode) const
{
	// Find the node with the smallest prefix in the subtree from thisNode

    // Used as part of remove() algorithm

    // Check Lecture Notes for implementation
}


void objPosBST::remove(const objPos &thisPos, TNode* &thisNode)
{
	// Remove the node with matching prefix of thisPos from the subtree thisNode

    // *IMPORTANT* Check Lecture Notes for general implementation
    //  Remember the three removal case scenarios

    // Case 1 and 2 both can be handled with one algorithm (Lecture Notes)

    // Case 3 - Delete the node with 2 children
    //   You can use either methods (check lecture notes)
}

// Public Interface, Implemented
void objPosBST::remove(const objPos &thisPos)
{
    remove(thisPos, root); // recursive call on the private helper function
}

bool objPosBST::findGreater(const int numThreshold, const TNode* thisNode) const
{
    // Determine whether any nodes in the tree has the NUMBER field of objPos data member greater than numThreshold

    // WARNING - this one is not as straightforward.

    // Algorithm Suggestion
    //  1. If tree empty, just return false
    //  2. Recursively check if the any number on the LEFT subtree is greater than numThreshold
    //  3. Recursively check if the any number on the RIGHT subtree is greater than numThreshold
    //  4. Then, check if the number field of the objPos data in the current node is greater than numThreshold
    //  5. If any of the results from item 2, 3, and 4 is TRUE, return true.
    //     Otherwise, return false.

    // HINT:  If you do this right, the algorithm is less than 10 lines.
}

bool objPosBST::findGreater(const int numThreshold) const
{
    return findGreater(numThreshold, root);
}
