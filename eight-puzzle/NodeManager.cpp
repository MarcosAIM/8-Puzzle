#include "NodeManager.h"

NodeManager::NodeManager(int nodes_generated, char char_pos) {
    this->nodes_generated = nodes_generated;
    this->char_pos = char_pos;
}

/*
 * Function: setParent
 * :first parameter: Node * child , second parameter Node * parent.
 * :sets the first param child previous Node pointer, to second parameter parent.
 * :Node class has a previous Node pointer to point to a previous Node.
 * :Returns: (void)
 * */
void NodeManager::setParent(Node * child, Node * parent) {
    if (child != nullptr && parent != nullptr){
        child->previous = new Node(parent->puzzle);
        child->previous->g_value = parent->g_value;
        child->previous->previous = parent->previous;
    }
}

/*Function: generateLeftNode
 * :first parameter: Node * node
 * :takes a node and returns the next node by moving the pos character left, the position of
 * the pos character must be determined before calling this function.
 * :function also updates the generated node's position of the character.
 * :sets direction_moved char to l
 * :Returns: Node *
 * */
Node *NodeManager::generateLeftNode(Node * node) {
    if(node->row_pos == 'x')
        NodeManager::findPosition(node);
    int row_pos = node->row_pos - '0';
    int col_pos = node->col_pos - '0';
    if(col_pos==0)
        return nullptr;
    else{
        Node* temp = new Node(node->puzzle);
        //moving blank space left
        temp->puzzle[row_pos][col_pos] = temp->puzzle[row_pos][col_pos-1];
        temp->puzzle[row_pos][col_pos-1]=this->char_pos;
        //set parent
        setParent(temp,node);
        //updating the position on the new node
        temp->row_pos = node->row_pos;
        temp->col_pos = static_cast<char>('0' + (col_pos - 1));
        //setting the movement char on the new node
        temp->direction_moved = 'l';
        this->nodes_generated++;
        return temp;
    }
}

/*Function: generateRightNode
 * :first parameter: Node * node
 * :takes a node and returns the next node by moving the pos character right, the position of
 * the pos character must be determined before calling this function.
 * :function also updates the generated node's position of the character.
 * :sets direction_moved char to r
 * :Returns: Node *
 * */
Node *NodeManager::generateRightNode(Node * node) {
    if(node->row_pos == 'x')
        NodeManager::findPosition(node);
    int row_pos = node->row_pos - '0';
    int col_pos = node->col_pos - '0';
    if(col_pos==2)
        return nullptr;
    else{
        Node* temp = new Node(node->puzzle);
        //moving blank space left
        temp->puzzle[row_pos][col_pos] = temp->puzzle[row_pos][col_pos+1];
        temp->puzzle[row_pos][col_pos+1] = this->char_pos;
        //set parent
        setParent(temp,node);
        //updating the position on the new node
        temp->row_pos = node->row_pos;
        temp->col_pos = static_cast<char>('0' + (col_pos + 1));
        //setting the movement char on the new node
        temp->direction_moved = 'r';
        this->nodes_generated++;
        return temp;
    }
}

/*Function: generateUpNode
 * :first parameter: Node * node
 * :takes a node and returns the next node by moving the pos character up, the position of
 * the pos character must be determined before calling this function.
 * :function also updates the generated node's position of the character.
 * :sets direction_moved char to u
 * :Returns: Node *
 * */
Node *NodeManager::generateUpNode(Node * node) {
    if(node->row_pos == 'x')
        NodeManager::findPosition(node);
    int row_pos = node->row_pos - '0';
    int col_pos = node->col_pos - '0';
    if(row_pos==0)
        return nullptr;
    else{
        Node* temp = new Node(node->puzzle);
        //moving blank space left
        temp->puzzle[row_pos][col_pos] = temp->puzzle[row_pos-1][col_pos];
        temp->puzzle[row_pos-1][col_pos] = this->char_pos;
        //set parent
        setParent(temp,node);
        //updating the position on the new node
        temp->col_pos = node->col_pos;
        temp->row_pos = static_cast<char>('0' + (row_pos - 1));
        //setting the movement char on the new node
        temp->direction_moved = 'u';
        this->nodes_generated++;
        return temp;
    }
}

/*Function: generateDownNode
 * :first parameter: Node * node
 * :takes a node and returns the next node by moving the pos character down, the position of
 * the pos character must be determined before calling this function.
 * :function also updates the generated node's position of the character.
 * :sets direction_moved char to d
 * :Returns: Node *
 * */
Node *NodeManager::generateDownNode(Node * node) {
    if(node->row_pos == 'x')
        NodeManager::findPosition(node);
    int row_pos = node->row_pos - '0';
    int col_pos = node->col_pos - '0';
    if(row_pos == 2)
        return nullptr;
    else{
        Node* temp = new Node(node->puzzle);
        //moving blank space left

        temp->puzzle[row_pos][col_pos] = temp->puzzle[row_pos+1][col_pos];
        temp->puzzle[row_pos+1][col_pos] = this->char_pos;
        //set parent
        setParent(temp,node);
        //updating the position on the new node
        temp->col_pos = node->col_pos;
        temp->row_pos = static_cast<char>('0' + (row_pos + 1));
        //setting the movement char on the new node
        temp->direction_moved = 'd';
        this->nodes_generated++;
        return temp;
    }
}

/*Function: printPuzzle
 * :Prints a 3-3 puzzle to console
 * :Returns: (void)
 * */
void NodeManager::printPuzzle(std::array<std::array<char, 3>, 3> puzzle) {
    std::cout << "_______" << std::endl;
    for(int r = 0; r < 3; r++ ){
        for(int c = 0; c < 3; c++ ){
            std::cout << "|" << puzzle[r][c];
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-------" << std::endl;
}

/*Function: printPuzzle
 * :Finds the position of the determined pos character and sets the Node row_pos and col_pos
 * :to the determined row position and column position.
 * :Returns: (void)
 * */
void NodeManager::findPosition(Node * node) const {
    if(node->row_pos == 'x'){
        for(int r = 0; r < 3; r++ ){
            for(int c = 0; c < 3; c++ ){
                if (node->puzzle[r][c]==this->char_pos){
                    node->row_pos = static_cast<char>('0' + r);
                    node->col_pos = static_cast<char>('0' + c);
                }
            }
        }
    }
}
