#include <GLT/RefCount.hpp>
using namespace GLT;


// Reference count printing switch
//#define _GLT_DO_REF_COUNT_PRINT


// Optionally include iostream
#ifdef _GLT_DO_REF_COUNT_PRINT
#include <iostream>
#endif


// Create the reference counter
RefCount::RefCount(void) {
  this->referenceCount = new unsigned(0);
  #ifdef _GLT_DO_REF_COUNT_PRINT
    std::cout << "Refcount " << this->referenceCount
              << " created\n";
  #endif
}


// Copy constructor with increment
RefCount::RefCount(const RefCount& other) {
  this->referenceCount = other.referenceCount;
  this->Increment();
  #ifdef _GLT_DO_REF_COUNT_PRINT
    std::cout << "Refcount " << this->referenceCount
              << " incremented (copy) "
              << *this->referenceCount << "\n";
  #endif
}


// Assignment operator
RefCount& RefCount::operator=(const RefCount& other) {
  if(this == &other) {
    return *this;
  } else {
    this->referenceCount = other.referenceCount;
    this->Increment();
    #ifdef _GLT_DO_REF_COUNT_PRINT
      std::cout << "Refcount " << this->referenceCount
                << " incremented (assign) "
                << *this->referenceCount << "\n";
    #endif
    return *this;
  }
}


// Destructor, decrement reference counter
RefCount::~RefCount(void) {
  if(this->GetReferenceCount() != 0) {
    this->Decrement();
    #ifdef _GLT_DO_REF_COUNT_PRINT
      std::cout << "Refcount " << this->referenceCount
                << " decremented "
                << *this->referenceCount << "\n";
    #endif
  } else {
    #ifdef _GLT_DO_REF_COUNT_PRINT
      std::cout << "Refcount " << this->referenceCount
                << " destroyed\n";
    #endif
    delete this->referenceCount;
  }
}
