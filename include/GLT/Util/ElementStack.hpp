#ifndef GLT_ELEMENT_STACK_INCLUDED
#define GLT_ELEMENT_STACK_INCLUDED


// This project
#ifndef GLT_GL_INCLUDED
#include "GLT/Extern/GL.hpp"
#endif


// standard
#include <vector>
#include <iostream>


namespace GLT {

  // Class defines a stack
  template <class T>
  class ElementStack {
  private:

    // Data storage
    std::vector<T> data;

  public:

    // Add an element to the top of the stack
    void Push(T element) {
      this->data.push_back(element);
    }

    // Pop element from stack and return popped value
    T Pop() {
      T top = this->Top();
      this->data.pop_back();
      return top;
    }

    // Top element on the stack
    T Top() {
      return this->data.back();
    }

    // Clear the stack of all data
    void Clear() {
      this->data.clear();
    }

    // Destructor, clear data
    ~ElementStack() {
      this->Clear();
    }
  };

} // namespace GLT


#endif // GLT_ELEMENT_STACK_INCLUDED
