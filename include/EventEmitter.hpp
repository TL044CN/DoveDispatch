/**
 * @file EventEmitter.hpp
 * @author TL044CN
 * @brief EventEmitter base class for extending other classes
 * @version 0.2
 * @date 2024-02-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Event.hpp"
#include <concepts>
#include <functional>
#include <memory>
#include <map>

namespace DoveDispatch {

class EventEmitter;

/**
 * @brief Concept to check if a class is an Event
 * 
 * @tparam T the class to check
 */
template<typename T>
concept EventType = std::is_base_of<Event, T>::value;

 /**
  * @brief Event Emitter base class to inherit from
  *
  */
class EventEmitter {
public:
    /**
     * @brief Listener function that is called when an Event is emitted
     *
     */
    using CallbackFn = std::function<void(std::shared_ptr<Event>)>;

private:
    std::map<Event::DescriptorType, std::vector<CallbackFn>> mListeners;

private:
    /**
     * @brief Adds a listener to the Listeners map that is called when the given Event is emitted
     *
     * @param descriptor the Descriptor of the Event to listen to
     * @param callback the Callback Function to call
     */
    void on_impl(const Event::DescriptorType& descriptor, CallbackFn&& callback);

public:

    /**
     * @brief Adds a Listener for the given Event
     *
     * @code{.cpp}
     * MyEmitter.on<MyEvent>(std::bind(&MyClass::myHandle, this, std::placeholders::_1));
     * @endcode
     *
     * @tparam Evt the Event to listen to
     * @param callback the callback function
     */
    template<EventType Evt> requires
        std::is_default_constructible<Evt>::value
    void on(std::function<void(const Evt&)> callback) {
        on_impl(Evt().type(),
        [functor = std::move(callback)]
        (const std::shared_ptr<Event>& event) -> void {
            const auto& evt = *static_cast<Evt*>(&*event);
            functor(evt);
        });
    }

protected:
    /**
     * @brief Emits the given Event, calling all Listeners
     * @code{.cpp}
     * auto& myEvtPtr = myEmitter.emit(new MyEvent());
     * @endcode
     * @note Events should be created in this function,
     *       because Ownership is transfered to the emitter
     * @param event the Event to emit
     * @return std::shared_ptr<Event> shared Pointer to the newly dispatched Event
     */
    std::shared_ptr<Event> emit(Event*&& event) const;

};

}   // namespace DoveDispatch