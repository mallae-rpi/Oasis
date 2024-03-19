# Differentiation Programming

The following notes contain useful information for implementing symbolic differentiation in code:

## Expression Trees
* The overall idea behind programming differentiation involves parsing the expression and storing operations in a tree structure.
* Recursive differentiation of the tree is recommended, applying differentiation rules to each node.
* For example, in the expression ```2x^2 + 5x```, the terms ```2x^2``` and ```5x``` can be represented as their own child nodes, while the ```+``` operator can be represented as a parent node.
* [Further reading] (https://stackoverflow.com/questions/2905518/derivative-calculator)