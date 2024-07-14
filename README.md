### Problem Statement

The Subset Sum Problem (SSP) is a classic decision problem in computer science. Given a multiset $S$ of integers and a target sum $T$, the problem asks whether any subset of the integers sums precisely to $T$. 

Our objective is to identify and list all subsets whose sum equals $T$.

Assumption : We assume that we are dealing with $positive$ integers only.

### Task

We aim to explore the ideas from the paper [found here](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=bccf6a78e6e9473a96e2b876451635a459dbcb96) to solve the Subset Sum Problem. The proposed solution involves finding a cut randomly and then recursively identifying all other cuts.

### Lattice Structure

The nodes correspond to the subsets of the integers in the multiset $S$. A node $v$ is a child of the node $u$ in the lattice if  $u \subset v$  and $u$ and $v$ differ by exactly one element. The node $u$ is a parent of the node $v$.

![alt text](Images/Graph%20Lattice.jpeg)
The above lattice is for N=4, Multiset = {1,3,4,6} , Target T = 7

We define infrequent lattice node as subset having sum > T . Similarly frequent lattice nodes are defined as subsets having sum <=T . If a frequent lattice node is a parent of an infrequent lattice node,we call the edge  a cut.
By definition,Any subset having sum equal to K will be part of atleast one cut,or it will be containing all the elements of the multiset.
A total of 12 cuts are present in the above example.Our algorithm will pick up one of the cuts randomly and explore all other cuts recursively.While exploring the cuts , we will simultaneously check if the parent lattice node is having subset sum equal to K.

### Implementation Details

#### Data Structures 

1. `std::unordered_map` to store the $visited$ table. We should be using a custom hash function instead of relying on the default `std::hash` used by `std::unordered_map` .
2. `std::set` to store child lattice node and parent lattice node for a cut. Instead of storing both the sets, we can store the set for child lattice node only along with the element to be removed to derive the parent lattice node. 

#### Algorithm

The algorithm remains very similar to what has been described in the paper.
1. Find an initial cut by randomly adding elements until the sum of the elements is $>T$
2. Recursively Invoke ExpandCut Algorithm to find other cuts. While exploring cuts also check if the size of the parent lattice node is equal to $T$.

### Tests
To ensure accuracy , we have generated more than 100 tests. All the tests can be run by invoking `python3 tests/script.py` from the $root$ directory.
The test inputs are provided in the `tests/input.txt` file, with their corresponding outputs in the `tests/output.txt` file.

##### Input Format
- `N`: Number of elements in the array.
- `K`: Target sum.
- $A_1$, $A_2$, ..., $A_N$: The elements of the array.

##### Output Format
- `M`: Number of subsets having a sum equal to `K`.


### Optimizations

1. **Use BFS instead of DFS**: Iterative traversal with BFS requires less memory compared to DFS.
2. **Avoid redundant invocations**: For a cut (P, C), where P is the parent lattice node and C is the lattice node, once `ExpandCut` is invoked on (P, C), we can skip invoking the algorithm on cuts (P', C). It can be proven that the algorithm still visits all the cuts.





