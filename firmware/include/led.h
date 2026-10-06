/**
 * @file led.h
 * @brief RGB debug LED helper functions.
 *
 * Provides helper functions for controlling the RGB status LED used during
 * development and debugging.
 *
 * LED functionality can be conditionally enabled or disabled at compile time.
 */

#pragma once

#include "esphome.h"

//#define DEBUG_LED                 /**< Comment this line to disable debug LED */

/**
 * @brief Lights Debug LED in yellow color.
 * 
 */
inline void ledBoot()
{
#ifdef DEBUG_LED
    id(status_led).turn_on()
      .set_rgb(1,0.7,0)
      .perform();
#endif
}

/**
 * @brief Lights Debug LED in blue color.
 * 
 */
inline void ledConnect()
{
#ifdef DEBUG_LED
    id(status_led).turn_on()
      .set_rgb(0,0,1)
      .perform();
#endif
}

/**
 * @brief Lights Debug LED in green color.
 * 
 */
inline void ledClient()
{
#ifdef DEBUG_LED
    id(status_led).turn_on()
      .set_rgb(0,1,0)
      .perform();
#endif
}

/**
 * @brief Lights Debug LED in red color.
 * 
 */
inline void ledDisconnect()
{
#ifdef DEBUG_LED
    id(status_led).turn_on()
      .set_rgb(1,0,0)
      .perform();
#endif
}

/**
 * @brief Lights Debug LED in purple color.
 * 
 */
inline void ledRefresh()
{
#ifdef DEBUG_LED
    id(status_led).turn_on()
      .set_rgb(1,0,1)
      .perform();
#endif
}