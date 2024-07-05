### Problem Statement

The Subset Sum Problem (SSP) is a classic decision problem in computer science. Given a multiset $S$ of integers and a target sum $T$, the problem asks whether any subset of the integers sums precisely to $T$. 

Our objective is to identify and list all subsets whose sum equals $T$.

### Task

We aim to explore the ideas from the paper [found here](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=bccf6a78e6e9473a96e2b876451635a459dbcb96) to solve the Subset Sum Problem. The proposed solution involves finding a cut randomly and then recursively identifying all other cuts.

### Lattice Structure

Thenodes correspond to the subsets of the integers in the multiset $S$. A node $v$ is a child of the node $u$ in the lattice if  $u \subset v$  and $u$ and $v$ differ by exactly one element. The node $u$ is a parent of the node $v$.

![alt text](Images/Graph%20Lattice.jpeg)

### Implementation Details

Data Structures : 

1. `std::unordered_map` to store the $visited$ table. We should be using a custom hash function instead of relying on the default `std::hash` used by `std::unordered_map` .
2. `std::set` to store child lattice node and parent lattice node for a cut. Instead of storing both the sets, we can store the set for child lattice node only along with the element to be removed to derive the parent lattice node. 

Algorithm : 

The algorithm remains very similar to what has been described in the paper.
1. Find an initial cut by randomly adding elements until the sum of the elements is $>T$
2. Recursively Invoke ExpandCut Algorithm to find other cuts. While exploring cuts also check if the size of the parent lattice node is equal to $T$. 
