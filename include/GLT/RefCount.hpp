#ifndef _GLT_REF_COUNT_INCLUDED
#define _GLT_REF_COUNT_INCLUDED


namespace GLT {

  // Reference counter class
  class RefCount {
  private:

    // Increment and decrement methods
    void Increment(void) {(*this->referenceCount)++;}
    void Decrement(void) {(*this->referenceCount)--;}

    // Shared counter
    unsigned *referenceCount;

  public:

    // Construct, count starts at zero
    RefCount(void);

    // Copy constructor
    RefCount(const RefCount& other);

    // Assignment operator
    RefCount& operator=(const RefCount& other);

    // Get reference counter value
    unsigned GetReferenceCount(void) {return *this->referenceCount;}
    bool ReferencedElsewhere(void) {return *this->referenceCount;}

    // Destroy when reference counter is zero
    ~RefCount(void);
  };

} // namespace GLT


#endif /// _GLT_REF_COUNT_INCLUDED
