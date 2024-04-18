# Dove Dispatch

[![Build Status](https://jenkins.shodan.fyi/buildStatus/icon?job=DoveDispatch)](https://jenkins.shodan.fyi/job/DoveDispatch/)
A simple Event System, for easily creating Event Emitting classes with Events that can hold data if desired.

## Example Usage

### Create a new Event Type

```c++
#include <string>

#include "Event.hpp"
using DoveDispatch::Event;

class MyEvent : public Event {
private:
    std::string mMyEventPayload;

public:

    // override the type function to make the Event work
    inline virtual DescriptorType type() const override {
        return "MyEvent";
    }

    // define how the Event should be constructed when emitted
    MyEvent(const std::string& text) : mMyEventPayload(text) {}

    // helper function for retrieving the text. (optional, for your use only)
    inline std::string getText() const { return mMyEventPayload; }
}
```

### Create a new Class that can emit custom Events

```c++
#include <string>

#include "MyEvent.hpp"
#include "EventEmitter.hpp"
using DoveDispatch::EventEmitter;

// Create some Class that emits the Event
class MyEventEmitter : public EventEmitter {
public:
    // custom function to emit the previously defined event
    void emitMyEvent(const std::string& text) const {
        emit(new MyEvent(text));
    }
}
```

### Listening to Events from the new EventEmitter Class

```c++
#include "MyEventEmitter.hpp"
#include "MyEvent.hpp"

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
