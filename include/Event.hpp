/**
 * @file Event.hpp
 * @author TL044CN
 * @brief Event class for extending the Event System
 * @version 0.2
 * @date 2024-02-06
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
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
