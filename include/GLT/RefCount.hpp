#ifndef _GLT_REF_COUNT_INCLUDED
#define _GLT_REF_COUNT_INCLUDED


namespace GLT {

  // Reference counter class
  class RefCount {
  private:

    // Shared counter
    int *count;

    // Increment and decrement methods
    void Increment(void) {*this->count++;}
    void Decrement(void) {*this->count--;}

  public:

    // Construct, count starts at zero
    RefCount(void);

    // Copy constructor
    RefCount(const RefCount& rc);

    // Get reference counter value
    int GetCount(void) {return *this->count;}

    // Destroy when reference counter is zero
    ~RefCount(void);
  };

} // namespace GLT


#endif /// _GLT_REF_COUNT_INCLUDED
