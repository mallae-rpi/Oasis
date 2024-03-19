# Differentiation Programming

The following notes contain useful information for implementing symbolic differentiation in code:

## Expression Trees
* The overall idea behind programming differentiation involves parsing the expression and storing operations in a tree structure.
* Recursive differentiation of the tree is recommended, applying differentiation rules to each node.
* For example, in the expression ```2x^2 + 5x```, the terms ```2x^2``` and ```5x``` can be represented as their own child nodes, while the ```+``` operator can be represented as a parent node.
* [Further reading](https://stackoverflow.com/questions/2905518/derivative-calculator)

## Simplifying the Implementation

* Immutable data structures are suggested to be used to represent expressions. This is most likely to maximize efficiency so that the program does not have to account for possible changes to the expression.
* The Boehm garbage collector was suggested to be used. More research will be conducted to find out why. [Boehm garbage collector website](https://hboehm.info/gc/)
* To map each variable to a coefficient, use a finite map.
* Consider embedding Lua in C++ code.
* [Further reading](https://stackoverflow.com/questions/422594/derivatives-in-c-c)