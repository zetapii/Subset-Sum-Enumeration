# Work Log

## Progress Update

Following our discussion in the meeting on July 31st, we implemented a basic recursive approach with pruning. Here are the key findings:

1. **Recursive Approach Performance**: 
   We discovered that the recursive method is performing significantly better than the MARGIN algorithm. The primary reason for this is the reduced space complexity and not generating duplicate subsets.

2. **Space Complexity**:
   - Recursive Approach: The space complexity remains linear in N (where N is the number of elements in the set).
   - MARGIN Algorithm: The space complexity tends to grow exponentially, which is leading to performance issues for larger arrays.

3. **Pruning Effectiveness**:
   The pruning technique we implemented helps to cut off unnecessary branches in the recursion tree.


4. **Recursive Approach Advantages**:
   - No Additional Data Structures: The recursive approach doesn't require any additional complex data structures like hashmaps.
   - No Duplicate Sets: Unlike the MARGIN algorithm, the recursive method naturally avoids generating duplicate sets, which contributes to its efficiency.

5. **Issue with Enumerating all subsets** :

   While enumerating all subsets at a particular level seemed like a promising approach, we've identified a significant challenge:

   - **Combinatorial Explosion**: For larger sets, the number of subsets at a particular level can become extremely large. For example, in a set of 30 elements, the number of 10-element subsets (30 choose 10) 
   is 30045015. This presents two main issues:
     a) The time required to generate and process all these subsets becomes impractical.
     b) Memory usage can also become an issue.


