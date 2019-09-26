#include "heaps/top/all.h"
#include "heaps/utility/all.h"
#include "utility/all.h"
#include "wrappers/all.h"
#include "heaplayers.h"

#include <unordered_map>
#include <vector>
#include <list>
#include <forward_list>
#include <unordered_set>
#include <set>
#include <queue>

#include "utility/all.h"
#include "heaps/objectrep/sizeheap.h"
#include "heaps/general/kingsleyheap.h"
#include "heaps/debug/debugheap.h"
#include "heaps/threads/lockedheap.h"

#define MAX_WORKING_SET_SIZE 1000 //Size of Working Set
#define COLD_SET_THRESHOLD 100 //Threshold size of Cold Set per size class

namespace SmashSTL {
  //STL classes for Smash. You should use these instead of C++ default STL.
  //These data structures uses their own heap for allocation, instead of malloc/free.
  //You are free to add more C++ STL classes if needed.
  class InternalTopHeap : public HL::SizeHeap<HL::BumpAlloc<16384 * 1024, HL::MmapHeap, 16>> {
  private:
    typedef HL::SizeHeap<HL::BumpAlloc<16384 * 1024, HL::MmapHeap, 16>> SuperHeap;

  public:
  };


  class InternalHeap : public HL::ExactlyOneHeap<HL::LockedHeap<HL::PosixLockType, HL::DebugHeap<HL::KingsleyHeap<HL::FreelistHeap<InternalTopHeap>, HL::MmapHeap>>>> {
  protected:
    typedef HL::ExactlyOneHeap<HL::LockedHeap<HL::PosixLockType, HL::DebugHeap<HL::KingsleyHeap<HL::FreelistHeap<InternalTopHeap>, HL::MmapHeap>>>>
        SuperHeap;
    
  public:
    InternalHeap() : SuperHeap() {
      static_assert(Alignment % 16 == 0, "16-byte alignment");
    }
  };

  template <typename K, typename V>
  using unordered_map = std::unordered_map<K, V, std::hash<K>, std::equal_to<K>, HL::STLAllocator<pair<const K, V>, InternalHeap>>;
  template <typename K>
  using unordered_set = std::unordered_set<K, std::hash<K>, std::equal_to<K>, HL::STLAllocator<K, InternalHeap>>;
  template <class T, class Compare=less<T>>
  using set = std::set<T, Compare, HL::STLAllocator<T, InternalHeap>>;
  template <typename T>
  using list = std::list<T, HL::STLAllocator<T, InternalHeap>>;
  template <typename T>
  using forward_list = std::forward_list<T, HL::STLAllocator<T, InternalHeap>>;
  template <typename T>
  using deque = std::deque<T, HL::STLAllocator<T, InternalHeap>>;
  template <typename T>
  using queue = std::queue<T, deque<T>>;
  template <typename T>
  using vector = std::vector<T, HL::STLAllocator<T, InternalHeap>>;
};

class SmashHeap {
  public:
    SmashHeap () {
      //Implement
    }

    void* malloc (size_t size) {
		//Implement malloc here
		return nullptr;
    }

    void free (void* ptr) {
		//Implement free
    }
};
