## Meeting Notes - 9th August, 2024
### Key Points

1. **Lexicographical Generation**: We generate subsets in lexicographical order.
2. **Frequent/Infrequent Identification**: We can identify frequent and infrequent subsets without generating them.
3. **Lexicographical Processing**: We process subsets in lexicographical order.

### Example

Consider a **Superset Cut Node** = `{1, 2, 3, 4}` and a **Subset Cut Node** = `{1, 2, 3}`. From `{1, 2, 3}`, we can generate **Sibling Cuts** as follows:

* `Sum({1, 2, 3}) - 3 + 4 => 1 added to sum`
* `Sum({1, 2, 3}) - 2 + 4 => 2 added to sum`
* `Sum({1, 2, 3}) - 1 + 4 => 3 added to sum`

### Questions

1. **K-Size Subset Coverage**: Will the process examine all subsets of size K?
2. **Duplicate Generation**: Can two subsets of size K, in lexicographical order, generate the same subset of size K + 1?