# Meeting Notes - 31st July, 2024

## Topics Discussed

### 1. Identifying Inefficiencies in MARGIN Approach

- Investigate which step of the MARGIN algorithm is causing visits to duplicate subsets
- Analyze the current implementation to pinpoint the source of redundancy

### 2. Level-based Subset Enumeration

- Explore the possibility of fixing a specific level in the lattice structure
- Enumerate subsets at the chosen level
- Develop a strategy to navigate up/down the lattice based on the fixed level
- Discuss the potential benefits and drawbacks of this approach compared to the current implementation

## Action Items

1. Review the MARGIN algorithm implementation and identify the step(s) causing duplicate subset visits
2. Develop a prototype for level-based subset enumeration
3. Compare the performance of the current approach with the level-based enumeration