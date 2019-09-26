#include <stdio.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <cstring>
#include <sys/signal.h>

#include "SmashHeap.h"

static SmashHeap* smashHeap = nullptr;
static char thBuf[sizeof(SmashHeap)];
static bool initializing_heap = false;
static bool signal_set = false;

typedef void (*SignalHandlerType) (int signum, siginfo_t* info, void* arg);

void segv_handler (int signum, siginfo_t* info, void* arg) {
	//Implement the signal handler
}

struct sigaction setSignalHandler (int _sig, SignalHandlerType _sig_handler) {
	// Install segv_handler as the handler for given signal.
	struct sigaction sa;
	struct sigaction prev_sa;

    memset (&sa, 0, sizeof (sa));
    sa.sa_sigaction = _sig_handler;
    sa.sa_flags = SA_SIGINFO;

    if (sigaction (_sig, &sa, &prev_sa) == -1) {
    	printf ("Error: Cannot set sigaction\n");
    	perror ("");
	    abort ();
    }
  
	return prev_sa;
}

__attribute__((constructor))
void lib_constructor () {
	//Install SIGSEGV handler before the program starts running
  	struct sigaction prev_segv_handler;
  
	if (signal_set)
    	return;

	prev_segv_handler = setSignalHandler (SIGSEGV, segv_handler);
  	signal_set = true;
}


inline static SmashHeap* getSmashHeap () {
    //Get SmashHeap and initialize it if not initialized
    if (smashHeap == nullptr) {
        initializing_heap = true;
        smashHeap = new (thBuf) SmashHeap ();
    }

    return smashHeap;
}

extern "C" {
void *malloc(size_t size) {
    if (smashHeap == nullptr && initializing_heap == true) {
		//When heap is not initialized and it is getting initialized use
		//mmap instead of malloc to avoid recursion
        return mmap (0, size, PROT_READ|PROT_WRITE, 
					 MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    }
    
    if (!signal_set) {
		//Set signal if it has not been set
        lib_constructor ();
	}

    void *p = NULL;
	//Allocate from the heap
    p = getSmashHeap ()->malloc (size);
    initializing_heap = false;
    return p;
}

void free (void* p) {
	//Implement free
}

void* realloc (void* p, size_t size) {
	//Implement realloc 
	return nullptr;
}

void* calloc (size_t nmemb, size_t size) {
	//Implement calloc
	return nullptr;
}
}
