#include <EventEmitter.hpp>

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
