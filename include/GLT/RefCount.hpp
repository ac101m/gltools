#ifndef _GLT_REF_COUNT_INCLUDED
#define _GLT_REF_COUNT_INCLUDED


// This project
#ifndef _GLT_MASTER_INCLUDED
#include <GLT/Master.hpp>
#endif


namespace GLT {

  // Referenc
  class RefCount {
  private:
    int *count;

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
