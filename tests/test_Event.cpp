#include "catch2/catch.hpp"
#include "Event.hpp"

// Derived class that implements all the pure virtual functions of the 'Event' class
class DerivedEvent : public Event {
public:
    virtual DescriptorType type() const override {
        return "DerivedEvent";
    }
};

TEST_CASE("Event destructor test") {
    SECTION("Event object is destroyed") {
        Event* event = new DerivedEvent(); // Allocate an object of the derived class
        delete event;
        // No assertion needed, just checking if the destructor is called without any errors
    }
}