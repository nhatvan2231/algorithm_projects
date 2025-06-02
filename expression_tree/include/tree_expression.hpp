#ifndef TREE_EXPRESSION_HPP
#define TREE_EXPRESSION_HPP

#include <iostream>
#include <format>
#include <sstream>
#include <string>
#include <regex>

class Node {
	// Node of a tree
	public:
		// Operand numerical or literal or operators
		enum Type {OPERAND_N, OPERAND_L, SUB, ADD, MUL, DIV};
		Node();
		~Node();
		// Scanning new node to store correct type and value
		Node(std::string);
		// Return a string value representation
		std::string dump();
		// TreeExpr and Stack objects can access the type and value
		friend class TreeExpr;
		friend class Stack;
	private:
		// Type
		Type type;
		// String value
		std::string svalue;
		// Numberical value
		double dvalue;
		// Left child
		Node* left = NULL;
		// Right child
		Node* right = NULL;
		// next linked node for stack implementation
		Node* next = NULL;
};

class Stack{
	// Stack implementation using linked list
	public:
		Stack();
		~Stack();
		// Push node to stack
		void push(Node*);
		// Pop node from stack
		Node* pop();
		// TreeExpr object can access top of the stack
		friend class TreeExpr;
	private:
		// Top of the stack
		Node* top = NULL;
};

class TreeExpr {
	public:
		TreeExpr();
		~TreeExpr();
		// Build a tree from postfix expression
		bool postfix_to_tree(std::string);
		// Compute the infix expression
		void infix();
		// Compute the prefix expression
		void prefix();
		// Display the tree
		void print_tree(const std::string& ,Node*, bool);
	private:
		void infix_traversal(Node*);
		double prefix_traversal(Node*);
		Stack* tree_stack;
		// final result of the expression
		double result = 0;
};
#endif

