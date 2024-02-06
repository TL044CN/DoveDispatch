/**
 * @file Event.hpp
 * @author TL044CN (gunnisan2@web.de)
 * @brief Event class for extending the Event System
 * @version 0.1
 * @date 2024-02-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef TT_EVENT_HPP
#define TT_EVENT_HPP

#include <cstdint>

 /**
  * @brief Event Base class to inherit from
  * @note adding static constexpr DescriptorType = "...";
  *       should be done to derived classes
  */
class Event {
private:
    uint32_t mID = 0;

public:
    /**
     * @brief Descriptor Type of the Event Class
     */
    using DescriptorType = const char*;

    virtual ~Event();

    /**
     * @brief Returns the Type of the Event. This is used for differentiating Events during dispatch
     *
     * @return DescriptorType type of the Event
     */
    virtual DescriptorType type() const = 0;
};

#endif