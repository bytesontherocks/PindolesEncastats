#include <iostream>
#include <memory>

class Node : public std::enable_shared_from_this<Node> {
  public:
    struct Port {
        Node& parent;

        Port(Node& parent) : parent(parent) {}
        ~Port() { std::cout << "Port destructor!" << std::endl; }

        // this is the fancy bit: we get a pointer to Port but linked to the parent (Node)
        // shared_ptr, so the port shared_ptr influences the parent shared_ptr ref count. If the
        // parent can't be deleted while the Child shared_ptr is in used
        std::shared_ptr<Port> get_shared_ptr() {
            return std::shared_ptr<Port>(parent.shared_from_this(), this);
        }

        void say_hello() { std::cout << "Hello from Port!" << std::endl; }
    };

    Port port;

    Node() : port(*this) {}
    ~Node() { std::cout << "Node destructor!" << std::endl; }
};

int main() {
    auto node = std::make_shared<Node>();

    std::cout << "Node ref count: " << node.use_count() << std::endl;
    std::cout << "Get shared pointer to child" << std::endl;
    std::shared_ptr<Node::Port> childPtr = node->port.get_shared_ptr();
    std::cout << "Node ref count: " << node.use_count() << std::endl;

    std::cout << "Node pointer is reset:" << std::endl;

    node.reset();
    // When node.reset() is called, the reference count of node goes down to 0 because the
    // shared_ptr to node is reset. However, because childPtr still holds a shared pointer to Port,
    // which in turn holds a shared pointer to Node (via shared_from_this()), the Node object is not
    // destroyed yet.
    std::cout << "Node ref count: " << node.use_count() << std::endl;

    childPtr->say_hello();  // Works!

    return 0;
}