#include "catch2/catch.hpp"
#include "Event.hpp"
#include "EventEmitter.hpp"

using namespace DoveDispatch;

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

    std::shared_ptr<Event> pub_emit(std::unique_ptr<Event>&& event) const {
        return EventEmitter::emit(std::move(event));
    }
};

TEST_CASE("EventEmitter tests") {
    TestEventEmitter emitter;

    SECTION("Listener Tests") {
        GIVEN("An event emitter") {
            WHEN("A Listener is added"){
                THEN("The EventEmitter does not throw an exception") {
                    REQUIRE_NOTHROW(emitter.on<TestEvent1>([](const TestEvent1&) {}));
                }
            }
            AND_GIVEN("A listener was added") {
                bool wasCalled = false;
                int callCount = 0;

                emitter.on<TestEvent1>([&callCount](const TestEvent1&) {
                    callCount++;
                });
                WHEN("When an event is emitted using in place raw pointer") {
                    THEN("The correct listener is called") {
                        emitter.pub_emit(new TestEvent1);

                        REQUIRE(callCount == 1);
                    }
                    THEN("The listener is not called when a different event is emitted") {
                        emitter.pub_emit(new TestEvent2);

                        REQUIRE(callCount == 0);
                    }
                    THEN("The listener is called multiple times when the event is emitted multiple times") {
                        emitter.pub_emit(new TestEvent1);
                        emitter.pub_emit(new TestEvent1);

                        REQUIRE(callCount == 2);
                    }
                }
                WHEN("When an event is emitted using in place unique pointer") {
                    THEN("The correct listener is called") {
                        emitter.pub_emit(std::make_unique<TestEvent1>());

                        REQUIRE(callCount == 1);
                    }
                    AND_THEN("The listener is not called when a different event is emitted") {
                        emitter.pub_emit(std::make_unique<TestEvent2>());

                        REQUIRE(callCount == 0);
                    }
                    AND_THEN("The listener is called multiple times when the event is emitted multiple times") {
                        emitter.pub_emit(std::make_unique<TestEvent1>());
                        emitter.pub_emit(std::make_unique<TestEvent1>());

                        REQUIRE(callCount == 2);
                    }
                }
                WHEN("When an event is emitted by moving a unique pointer") {
                    THEN("The correct listener is called") {
                        auto event = std::make_unique<TestEvent1>();
                        emitter.pub_emit(std::move(event));

                        REQUIRE(callCount == 1);
                    }
                    THEN("The listener is not called when a different event is emitted") {
                        auto event = std::make_unique<TestEvent2>();
                        emitter.pub_emit(std::move(event));

                        REQUIRE(callCount == 0);
                    }
                    THEN("The listener is called multiple times when the event is emitted multiple times") {
                        auto event1 = std::make_unique<TestEvent1>();
                        auto event2 = std::make_unique<TestEvent1>();
                        emitter.pub_emit(std::move(event1));
                        emitter.pub_emit(std::move(event2));

                        REQUIRE(callCount == 2);
                    }
                    THEN("the listener is called as many times as it's specific event is emitted") {
                        auto event1 = std::make_unique<TestEvent1>();
                        auto event2 = std::make_unique<TestEvent2>();
                        auto event3 = std::make_unique<TestEvent2>();
                        auto event4 = std::make_unique<TestEvent1>();
                        auto event5 = std::make_unique<TestEvent2>();

                        emitter.pub_emit(std::move(event1));
                        emitter.pub_emit(std::move(event2));
                        emitter.pub_emit(std::move(event3));
                        emitter.pub_emit(std::move(event4));
                        emitter.pub_emit(std::move(event5));

                        REQUIRE(callCount == 2);
                    }
                }
            }
        }
    }

}