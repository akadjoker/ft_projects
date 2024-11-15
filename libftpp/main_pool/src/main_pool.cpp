#include "pool.hpp"
#include <iostream>

static int ObjectsCount = 0;

class TestObject {
public:
    TestObject() { std::cout << "TestObject default constructor" << std::endl; ObjectsCount++; }
    TestObject(int value) { std::cout << "TestObject constructor with value [" << value << "]" << std::endl; ObjectsCount++; }
    ~TestObject() { std::cout << "TestObject destructor" << std::endl;  ObjectsCount--; }

    void sayHello() const { std::cout << "Hello from TestObject" << std::endl; }
};

int main() {
    // Create a Pool for TestObject
    Pool<TestObject> myPool;

    // Resize the pool to pre-allocate 5 objects
    // Should output the 5 "TestObject constructor"
    myPool.resize(5);

    // Acquire an object from the pool 
    Pool<TestObject>::Object obj1 = myPool.acquire(15);
    obj1->sayHello();  // Should output: "Hello from TestObject"

    {
        // Acquire another object in a different scope
        Pool<TestObject>::Object obj2 = myPool.acquire();
        obj2->sayHello();  // Should also output: "Hello from TestObject"
        // obj2 is released back to the pool when it goes out of scope
    }

    // Acquire another object; this should give us the object that obj2 pointed to
    Pool<TestObject>::Object obj3 = myPool.acquire();
    obj3->sayHello();  // Should output: "Hello from TestObject"

    Pool<TestObject>::Object obj4 = myPool.acquire();
    Pool<TestObject>::Object obj5 = myPool.acquire();
    Pool<TestObject>::Object obj6 = myPool.acquire();
    Pool<TestObject>::Object obj7 = myPool.acquire();
    Pool<TestObject>::Object obj8 = myPool.acquire();


     std::cout << "ObjectsCount: " << ObjectsCount << std::endl;   

    // obj1 and obj3 are released back to the pool when the program ends
    return 0;
}
