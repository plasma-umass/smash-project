COMPSCI 630 Assignment: **Smash** compressing allocator

Code structure:
1. `libSmash.cpp`: contains the definitions of malloc, free, realloc, and calloc functions with SIGSEGV handler. You should implement these.
2. `SmashHeap.h`: contains the SmashHeap class and C++ STL declarations.

To build the project:
1. Clone [https://github.com/emeryberger/Heap-Layers](HeapLayers) to the main directory of project.
2. Clone [https://github.com/facebook/zstd](zstd) to the main directory of project and build it according to the build instructions.
3. Execute ```make``` to build `libSmash.so`
4. For a debug build use ```make libSmash-debug.so```.
