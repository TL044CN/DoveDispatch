#include "catch2/catch.hpp"
#include "Event.hpp"

#include <string>

// Derived class that implements all the pure virtual functions of the 'Event' class
class DerivedEvent : public Event {
public:
    virtual DescriptorType type() const override {
        return "DerivedEvent";
    }
};

TEST_CASE("Event test") {
    DerivedEvent* event = new DerivedEvent;

    SECTION("Event object is not null") {
        // Check if the event object is not null
        REQUIRE(event != nullptr);
    }

    SECTION("Event type is correct") {
        // Create a new DerivedEvent object
        REQUIRE(std::string(event->type()) == "DerivedEvent");
    }

    SECTION("Event object is deleted") {
        // Delete the event object
        delete event;

        REQUIRE(true);
    }
}