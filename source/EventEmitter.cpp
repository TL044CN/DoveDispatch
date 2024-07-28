#include "EventEmitter.hpp"

namespace DoveDispatch {

void EventEmitter::on_impl(const Event::DescriptorType& descriptor, CallbackFn&& callback) {
    mListeners[descriptor].push_back(callback);
}

std::shared_ptr<Event> EventEmitter::emit(Event*&& event) const {
    std::shared_ptr<Event> sharedEvent(event);
    auto type = event->type();
    if(mListeners.find(type) != mListeners.end())
        for(const auto& listener : mListeners.at(type))
            listener(sharedEvent);

    return sharedEvent;
}

std::shared_ptr<Event> EventEmitter::emit(std::unique_ptr<Event>&& event) const {
    return emit(event.release());
}

std::future<std::shared_ptr<Event>> EventEmitter::emit_async(Event*&& event) const {
    return std::async(std::launch::async, [this, evt = std::move(event)]() mutable {
        return emit(std::move(evt));
    });
}

std::future<std::shared_ptr<Event>> EventEmitter::emit_async(std::unique_ptr<Event>&& event) const {
    return emit_async(event.release());
}

}   // namespace DoveDispatch
