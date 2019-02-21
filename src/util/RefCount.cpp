#include <GLT/RefCount.hpp>
using namespace GLT;


// Create the reference counter
RefCount::RefCount(void) {
  this->count = new int(0);
}


// Copy constructor with increment
RefCount::RefCount(const RefCount& rc) {
  this->count = rc.count;
  this->Increment();
}


// Destructor, decement reference counter
RefCount::~RefCount(void) {
  if(this->GetCount() != 0) {
    this->Decrement();
  } else {
    delete this->count;
  }
}
