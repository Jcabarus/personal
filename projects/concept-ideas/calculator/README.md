# Calculator 

## Description
The purpose of this project is to demonstrate how parsing is implemented in computers, how they work, and how to deal with synatax.

How it works:
1. Reads in an expression based on the input
1. Converts the expression in to tokens i.e **operators** and **operands**
1. Builds a syntax tree based on the operator's precedence
1. Traverses the tree in **Post Order** (left, right, root)

## Installation
`g++ src/calculator.cpp src/pratt_parsing.c -o calculator` <br>