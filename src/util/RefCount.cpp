#include <GLT/RefCount.hpp>
using namespace GLT;


// Create the reference counter
RefCount::RefCount(void) {
  this->count = new int(0);
}


// Copy constructor with increment
RefCount::RefCount(const RefCount& rc) {
  this->count = rc.count;
  (*this->count)++;
}


// Destructor, decement reference counter
RefCount::~RefCount(void) {
  if(*this->count != 0) {
    (*this->count)--;
  } else {
    delete this->count;
  }
}
