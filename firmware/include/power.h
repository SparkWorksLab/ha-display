/**
 * @file power.h
 * @brief Power management and deep sleep helper functions.
 *
 * Provides functions for calculating the required deep sleep duration based
 * on the current time and the configured sleep schedule.
 *
 * The display uses a regular refresh interval during the day and a single
 * extended deep sleep period during the configured nighttime interval.
 */

#pragma once

#include "esphome.h"

/**
 * @brief Calculates the deep sleep duration based on the current time.
 *
 * During daytime, the device sleeps for the normal refresh cycle (15min).
 * During the configured sleep period, it sleeps until sleep_end_hour.
 *
 * @param sleep_start_hour Hour when the extended sleep period starts [0, 23].
 * @param sleep_end_hour Hour when the device wakes from extended sleep [0, 23].
 * @return Deep sleep duration in milliseconds.
 */
inline uint32_t getSleepDuration(
    int sleep_start_hour,
    int sleep_end_hour)
{

    /**< Validate sleep hour parameters. */
    if (sleep_start_hour < 0 || sleep_start_hour > 23 ||
        sleep_end_hour < 0 || sleep_end_hour > 23 ||
        sleep_start_hour == sleep_end_hour)
    {
        return 15UL * 60UL * 1000UL;
    }

    auto now = id(ha_time).now();

    /**< Fallback if time is not available. */
    if (!now.is_valid())
        return 15UL * 60UL * 1000UL;

    /**< Check whether the sleep period crosses midnight. */
    bool crosses_midnight =
        sleep_start_hour > sleep_end_hour;

    bool is_sleep_time;

    if (crosses_midnight)
    {
        /**< Sleep period crosses midnight. */
        is_sleep_time =
            now.hour >= sleep_start_hour ||
            now.hour < sleep_end_hour;
    }
    else
    {
        /**< Sleep period occurs within the same day. */
        is_sleep_time =
            now.hour >= sleep_start_hour &&
            now.hour < sleep_end_hour;
    }

    /**< Day time: normal Sleep Time refresh interval. */
    if (!is_sleep_time)
        return id(ha_sleep_duration).state * 60UL * 1000UL;

    uint32_t seconds_until_wake;

    if (crosses_midnight && now.hour >= sleep_start_hour)
    {
        /**< Time remaining today plus time until the wake hour tomorrow. */
        seconds_until_wake =
            ((24 - now.hour + sleep_end_hour - 1) * 3600UL) +
            ((59 - now.minute) * 60UL) +
            (60 - now.second);
    }
    else
    {
        /**< Time remaining until the wake hour today. */
        seconds_until_wake =
            ((sleep_end_hour - 1 - now.hour) * 3600UL) +
            ((59 - now.minute) * 60UL) +
            (60 - now.second);
    }

    return seconds_until_wake * 1000UL;
}