### Problem Statement

The Subset Sum Problem (SSP) is a classic decision problem in computer science. Given a multiset $S$ of integers and a target sum $T$, the problem asks whether any subset of the integers sums precisely to $T$. 
Our objective is to identify and list all subsets whose sum equals $T$.

### Task

We aim to explore the ideas from the paper [found here](https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=bccf6a78e6e9473a96e2b876451635a459dbcb96) to solve the Subset Sum Problem. The proposed solution involves finding a cut randomly and then recursively identifying all other cuts.

### Lattice Structure

Thenodes correspond to the subsets of the integers in the multiset $S$. A node $v$ is a child of the node $u$ in the lattice if  $u \subset v$  and $u$ and $v$ differ by exactly one element. The node $u$ is a parent of the node $v$.
