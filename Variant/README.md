# Visitor pattern implementations
This embedded pill explores different approaches implementing the visitor pattern. <br> **Inspired by the book C++ Software Design by Klaus Iglberger.** </br>

## Procedural Solution
We have and enum with different types, depending on the type the function does the action accordingly. It requires a switch case ANSI C style programming.
If you want to add a new type you need to update all the switch cases, if-else's, etc. It is a simple/primitive approach that leads to unmaintainable code
id the code base is big.

## Object-Oriented Solution
We have a pure interface class with virtual methods. The derived classes implement the methods according to their needs.
**Closed set of operations:** if you want to add a method to some specific class, the base and therefore all the derived classes will need to be updated even if for
some derived classes the method doesn't make sense.
**Open set of types:** adding a new type is as simple as adding a new derived class.

## The visitor design pattern 
Intent: “Represent an operation to be performed on the elements of an object structure.Visitor lets you define a new operation without changing the classes of the elements on which it operates.”
Main drawbacks:
    - Inflexibility: each type requires a visit function (imposed by the base). If, for a particular operation, all the functions are pretty much the same, they can't be re-used.
    - Add new types is more difficult due to the cyclic dependency between the Visitor base class and the type base class.

Use Visitor to extend operations

## std::variant solution: the one in this exercise
Visitor design pattern and based on procedural programming.
Open set of operations but closed set of types with some improvements respect the pure procedural like if a type is forgotten to be handled (using std::visit but not if switch case / get_if approach)

Despite these shortcomings, in summary, std::variant proves to be a
wonderful replacement for the OOP-based Visitor design pattern. It
simplifies the code a lot, removes almost all boilerplate code and
encapsulates the ugly and maintenance-intensive parts, and comes with
superior performance. In addition, std::variant proves to be another
great example of the fact that a design pattern is about an intent, not about
implementation details.