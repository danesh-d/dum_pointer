#include <cstdint>

class ReferenceCounter {
  private:
    uint32_t m_references;

  public:
    ReferenceCounter()
      : m_references(0) {
    }

    virtual ~ReferenceCounter() {
    }

    uint32_t addReference() {
      return ++m_references;
    }

    uint32_t releaseReference() {
      return --m_references;
    }
};

