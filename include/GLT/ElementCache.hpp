#ifndef _GLT_ELEMENT_CACHE_INCLUDED
#define _GLT_ELEMENT_CACHE_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


// Standard
#include <map>
#include <iostream>


namespace GLT {

  // Templated cache class, basically just a convenient wrapper for std::map
  template <class Tkey, class Tvalue>
  class ElementCache {
  private:

    // Data storage element
    std::map<Tkey, Tvalue> map;

  public:

    // Void constructor, empty to begin with
    ElementCache(void) {this->Clear();}

    // Clear the cache
    void Clear(void) {this->map.clear();}

    // Does the given element exist
    bool Exists(const Tkey& key) {
      return (this->map.find(key) != this->map.end());
    }

    // Get an element, error if not present
    Tvalue Get(const Tkey& key) {
      if(!this->Exists(key)) {
        std::cout << "Cache error, no matching key\n";
        exit(1);
      }
      return this->map.find(key)->second;
    }

    // Add an element, error if already present
    void Add(const Tkey& key, const Tvalue& value) {
      if(this->Exists(key)) {
        std::cout << "Cache error, key already exists\n";
        exit(1);
      }
      this->map.insert(std::pair<Tkey, Tvalue>(key, value));
    }
  };

}


#endif // _GLT_ELEMENT_CACHE_INCLUDED
