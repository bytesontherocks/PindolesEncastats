# Link list

## Ref counts

Ref count for Head:
- 0: list empty
- 1: list with more than one node. Head points to the first node
- 2: only one node in the list. Head and Tail point to the same node.

Ref count for Tail:
- 0: list empty
- 2: only one node in the list. 
    - Head and Tail point to the same node.
    - Node->next and Tail point to the same node.
