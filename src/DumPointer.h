
#include <cassert>

#include "ReferenceCounter.h"

template <typename T>
class DumPointer {
  private:
    T *m_objPtr;
    ReferenceCounter *m_rc;

  public:
    // Not alowed to have a dum pointer stand-alone!
    DumPointer() = delete;

    // Create a dum pointer which will embedd an object in itself.
    DumPointer(T *createdObjPtr)
      : m_objPtr(createdObjPtr),
        m_rc(new ReferenceCounter()) {
      assert(m_rc != nullptr);
      m_rc->addReference();
    }

    virtual ~DumPointer() {
      if (m_rc->releaseReference() == 0) {
        delete m_objPtr;
        delete m_rc;
      }
    }

    // Copy constructor.
    DumPointer(const DumPointer<T>& anotherObj)
      : m_objPtr(anotherObj.m_objPtr),
        m_rc(anotherObj.m_rc) {
      m_rc->addReference();
    }

    // Operator overloading for assignment. This will be called when an object
    // is copied.
    DumPointer<T>& operator=(const DumPointer<T>& anotherObj) {
      // No self assignment.
      if (this != &anotherObj) {
        // The current object will be replaced so decrement its reference and
        // release it if no one uses it.
        if (m_rc->releaseReference() == 0) {
          delete m_rc;
          delete m_objPtr;
        }

        // Perform the assignment.
        m_objPtr = anotherObj.m_objPtr;
        m_rc = anotherObj.m_rc;

        // Increment the reference of the newly assigned object.
        m_rc->addReference();
      }

      return *this;
    }

    // Operator overloading for de-referencing the object.
    T& operator* () {
      return *m_objPtr;
    }

    // Operator overloading for referencing the object.
    T* operator-> () {
      return m_objPtr;
    }
};

