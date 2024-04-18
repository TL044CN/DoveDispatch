# Dove Dispatch

[![Build Status](https://jenkins.shodan.fyi/buildStatus/icon?job=DoveDispatch)](https://jenkins.shodan.fyi/job/DoveDispatch/)
A simple Event System, for easily creating Event Emitting classes with Events that can hold data if desired.

## Example Usage

```c++
#include "Event.hpp"
#include "EventEmitter.hpp"

#include <string>

// Create a new Event Type
class MyEvent : public Event {
private:
    std::string mMyEventString;

public:

    inline virtual DescriptorType type() const override {
        return "MyEvent";
    }

    MyEvent(const std::string& text) : mMyEventString(text) {}

    inline std::string getText() const { return mMyEventString; }
}

// Create some Class that emits the Event
class MyEventEmitter : public EventEmitter {
public:
    void emitMyEvent(const std::string& text) const {
        emit(new MyEvent(text));
    }
}

int main() {

    // create the Emitter
    MyEventEmitter emitter;

    // listen for MyEvent from emitter
    emitter.on<MyEvent>([](const MyEvent* event) {
        std::cout << event.getText() << '\n';
    });


    // let the Emitter emit the event
    emitter.emitMyEvent("Custom Text Here");

    // the output should now show: "Custom Text Here\n"

    return EXIT_SUCCESS;
}
```
