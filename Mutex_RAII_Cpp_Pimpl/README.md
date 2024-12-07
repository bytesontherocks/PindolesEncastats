This is an example to show how using simple things from C++ can make the code more maintainable and less error prone.

In this example a simple case where we need to protect a resource with a mutex. The common approach is:

    AcquireMutex();
        UseResource();
    ReleaseMutex();

If we don't release the mutex we create a big problem that will lock the application until the watchdog or another protection triggers.

For a very economical price in terms of performance and memory we can get rid of the inconvinients of this approach just using 
RAII (Resource Acquisition Is Initialization) binding the life cycle of an object to the usage of the resource.

This is a good example where C++ offers a suitable mechanism for embedded systems:
 - no bloated code
 - no need of heap usage (dynamic memory allocation)

You just pay for what you use.

The example is provided using the std::thread interface. This example is for code testing purposes only because there is already a std::lock_guard
that does a similar thing.

The other example is base on CMSIS V2 but can be adapted to FreeRTOS, RTX, ThreadX, etc. if no CMSIS-V2 layer is found.
