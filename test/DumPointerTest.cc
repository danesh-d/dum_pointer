#include <iostream>
#include <string>
#include "../src/DumPointer.h"
#include "gtest/gtest.h"

class TestClass {
  private:
    bool *m_flag;
    std::string m_objName;

  public:
    TestClass(bool *flag, std::string objName)
      : m_flag(flag),
        m_objName(objName) {
      m_flag = flag;
      *m_flag = true;
    }

    ~TestClass() {
      *m_flag = false;
    }

    std::string ReturnText(std::string str) {
      return "DumPointer says: " + str;
    }
};

// Test if the object is created correctly.
TEST(DumPointerTest, create_a_dum_pointer) {
  bool flag = false;

  DumPointer<TestClass> ptr(new TestClass(&flag, "obj1"));

  EXPECT_EQ(ptr->ReturnText("Hi!"), "DumPointer says: Hi!");
  EXPECT_TRUE(flag);
}

// Test if the object is released correctly.
TEST(DumPointerTest, release_a_dum_pointer) {
  bool flag = false;
  TestClass *classPtr = nullptr;

  {
    classPtr = new TestClass(&flag, "obj2");
    DumPointer<TestClass> ptr(classPtr);

    EXPECT_EQ(ptr->ReturnText("Hi!"), "DumPointer says: Hi!");
    EXPECT_FALSE(classPtr == nullptr);
    EXPECT_TRUE(flag);
  }

  // Make sure that the object is correctly released when the object is out of
  // scope.
  EXPECT_FALSE(flag);
}

// Test reference counting mechanism.
TEST(DumPointerTest, reference_counting) {
  bool flag1 = false;
  bool flag2 = false;
  TestClass *classPtr1 = nullptr;
  TestClass *classPtr2 = nullptr;

  {
    classPtr1 = new TestClass(&flag1, "obj1");
    classPtr2 = new TestClass(&flag2, "obj2");

    // Reference counter for each object is equal to 1.
    DumPointer<TestClass> ptr1(classPtr1);
    DumPointer<TestClass> ptr2(classPtr2);

    EXPECT_EQ(ptr1->ReturnText("Hi!"), "DumPointer says: Hi!");
    EXPECT_EQ(ptr2->ReturnText("Hi!"), "DumPointer says: Hi!");
    EXPECT_FALSE(classPtr1 == nullptr);
    EXPECT_FALSE(classPtr2 == nullptr);
    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);

    // Now the reference counter for the second object is equal to 2 and the
    // reference counter for the first object should be zero. This means that
    // first object should be released now.
    ptr1 = ptr2;

    // Verify that the first object is released.
    EXPECT_FALSE(flag1);
  }

  // Verify that both objects are released.
  EXPECT_FALSE(flag1);
  EXPECT_FALSE(flag2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

