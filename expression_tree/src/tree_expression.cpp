#include "tree_expression.hpp"

Node::Node(){}
Node::~Node(){
	delete left;
	delete right;
}

Node::Node(std::string str){
	// Scanning for Operator and real number or literal
	std::regex number("(\\+|-)?[1-9][0-9]*(\\.[0-9]*)?|0(\\.[0-9]*)?");
	std::regex literal("[a-zA-Z]+");

	// Store string representation for later use
	svalue = str;

	// Store type and operand numerical value
	if (str == "-")
		type = Node::SUB;
	else if (str == "+")
		type = Node::ADD;
	else if (str == "*")
		type = Node::MUL;
	else if (str == "/")
		type = Node::DIV;
	else if (std::regex_match(str, number)){
		type = Node::OPERAND_N;
		dvalue = std::stof(str);
	}
	else if (std::regex_match(str, literal)){
		type = Node::OPERAND_L;
		// Only the first letter of the string
		dvalue = str[0];
	}
	else
		// Unknown input
		std::cout << std::format("Error: Unknown symbol '{}'", str) << std::endl;
}

std::string Node::dump(){
	// return the string representation
	return svalue;
}

Stack::Stack(){}
Stack::~Stack(){
	delete top;
}

void Stack::push(Node* n){
	// Push node to stack
	// If stack is empty top is node
	// Else replace top of the stack with new node
	// Old top is now next node in the stack
	if (top == NULL)
		top = n;
	else {
		n->next = top;
		top = n;
	}
}

Node* Stack::pop(){
	// Return top of stack
	// New top is the next top
	// if stack is empty return NULL
	if (top == NULL){
		return NULL;
	}
	Node* t = top;
	top = top->next;
	return t;
}

TreeExpr::TreeExpr(){}
TreeExpr::~TreeExpr(){
	delete tree_stack;
}

bool TreeExpr::postfix_to_tree(std::string str){
	// Take a postfix expression
	// Build a binary tree using a stack
	// The stack is implemented using linked list
	// When a node is pushed, new top is now the node
	// And the old top as next node linked to top
	// When pop, return top of the stack
	// And new top is the next node
	// The stack should only contain a root node of the tree

	// Allocate memory for a new tree
	tree_stack = new Stack();

	// parse the string to token and ignore whitespace
	std::istringstream sstr(str);
	std::string token;
	while ( sstr >> token){
		// new node for token
		Node* node = new Node(token);

		// node is a operator
		// the order of operator is larger than operand in the enum
		if (node->type > Node::OPERAND_L){
			// pop the first 2 nodes from the stack
			Node* right = tree_stack->pop();
			Node* left = tree_stack->pop();
			// checking if there are at least 2 operand for a operator
			if (left == NULL || right == NULL){
				std::cout << std::format("Error: Missing operand/s for '{}'", node->svalue) << std::endl;
				return false;
			}
			// build the subtree
			node->right = right;
			node->left = left;
		}
		// push to stack
		tree_stack->push(node);
	}

	// The stack should only contain a root node of the tree
	if (tree_stack->top->next != NULL){
		std::cout << std::format("Error: Invalid expression '{}'", tree_stack->top->dump()) << std::endl;
		return false;
	}
	std::cout << "\nBinary Tree:" << std::endl;
	// display the binary from the root
	print_tree("", tree_stack->top, false);
	return true;
}

void TreeExpr::print_tree(const std::string& prefix, Node* node, bool isleft){
	// Recursive through the tree
	// Instead of vertical tree
	// this is a horizontal tree
	if (node == NULL)
		return;
	std::cout << prefix;
	std::cout << (isleft?"|--":"'--") << '[' << node->dump() << ']' << std::endl;
	print_tree(prefix + (isleft? "|   ":"    "), node->left, true);
	print_tree(prefix + (isleft? "|   ":"    "), node->right, false);
}

void TreeExpr::infix(){
	// Return the infix expression using the tree
	// Get the root of the tree
	Node* infix_expr = tree_stack->top;
	// traversal from the root
	infix_traversal(infix_expr);
	std::cout << std::endl;
}

void TreeExpr::infix_traversal(Node* node){
	// Recursive through the tree
	if (node == NULL)
		return;
	// Display order: left operand -> operator -> right operand
	infix_traversal(node->left);
	std::cout << node->dump() << " ";
	infix_traversal(node->right);
}

void TreeExpr::prefix(){
	// Return the infix expression using the tree
	// Get the root of the tree
	Node* prefix_expr = tree_stack->top;
	// Traversal from the root
	// Also compute the expression
	result = prefix_traversal(prefix_expr);
	std::cout << std::endl << "Result: " << result << std::endl;
}

double TreeExpr::prefix_traversal(Node* node){
	// Recursive through the tree
	// Display order: operator -> left operand -> right operand
	std::cout << node->dump() << " ";
	// If node is a operator
	// Calculate using the left and right nodes numerical value
	if (node->type > Node::OPERAND_L){
		// Get nodes numerical value
		double left = prefix_traversal(node->left);
		double right = prefix_traversal(node->right);
		switch (node->type){
			case Node::ADD:
				return left + right;
			case Node::SUB:
				return left - right;
			case Node::MUL:
				return left * right;
			case Node::DIV:
				// Check for 0 division
				if(right == 0)
					std::cout << "Error: Can't divided by 0" << std::endl;
					return -1;
				return left / right;
		}
	}
	// Return the tree leaf numerical value
	return node->dvalue;
}

