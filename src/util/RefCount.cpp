#include <GLT/RefCount.hpp>
using namespace GLT;


// Create the reference counter
RefCount::RefCount(void) {
  this->count = new int(0);
}


// Copy constructor with increment
RefCount::RefCount(const RefCount& other) {
  this->count = other.count;
  this->Increment();
}


// Assignment operator
RefCount& RefCount::operator=(const RefCount& other) {
  if(this != &other) {
    this->count = other.count;
    this->Increment();
  }
}


// Destructor, decrement reference counter
RefCount::~RefCount(void) {
  if(this->GetCount() != 0) {
    this->Decrement();
  } else {
    delete this->count;
  }
}
