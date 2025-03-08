# Child Smart Pointer created from a parent Smart Pointer

The use case is a Node that has a Port. We want a shared pointer of the port individually and we want the port shared_ptr to be linked to the lifetime of the Node. If the Node is destroyed we don't want a dangling pointer to a port.
We achieve that creating a shared pointer child passing a shared pointer parent during construction.

When the parent shared pointer is reset it holds the destruction of the pointed object until the child ref count is 0.