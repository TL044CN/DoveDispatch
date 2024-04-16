#include "catch2/catch.hpp"
#include "Event.hpp"
#include "EventEmitter.hpp"

class TestEvent1 : public Event {
public:
    virtual DescriptorType type() const override {
        return "TestEvent1";
    }
};

class TestEvent2 : public Event {
public:
    virtual DescriptorType type() const override {
        return "TestEvent2";
    }
};

class TestEventEmitter : public EventEmitter {
public:
    std::shared_ptr<Event> pub_emit(Event* event) const {
        return EventEmitter::emit(std::move(event));
    }
};

TEST_CASE("EventEmitter tests") {
    TestEventEmitter emitter;

    SECTION("Listener is called when event is emitted") {
        bool wasCalled = false;

        emitter.on<TestEvent1>([&wasCalled](const TestEvent1&) {
            wasCalled = true;
        });

        emitter.pub_emit(new TestEvent1);

        REQUIRE(wasCalled);
    }

    SECTION("Listener is not called for different event type") {
        bool wasCalled = false;

        emitter.on<TestEvent1>([&wasCalled](const TestEvent1&) {
            wasCalled = true;
        });

        // Emitting a different type of event
        emitter.pub_emit(new TestEvent2);

        REQUIRE_FALSE(wasCalled);
    }

    SECTION("Multiple listeners are called") {
        int callCount = 0;

        emitter.on<TestEvent1>([&callCount](const TestEvent1&) {
            ++callCount;
        });

        emitter.on<TestEvent1>([&callCount](const TestEvent1&) {
            ++callCount;
        });

        emitter.pub_emit(new TestEvent1);

        REQUIRE(callCount == 2);
    }
}