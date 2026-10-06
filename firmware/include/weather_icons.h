/**
 * @file weather_icons.h
 * @brief Weather condition to display icon mapping.
 *
 * Provides helper functions and definitions for converting Home Assistant
 * weather condition strings into the corresponding Material Design icons
 * used by the e-paper display.
 */

#pragma once

#include <string>

/**
 * @brief Function to return weather icon from condition string.
 * 
 * @param condition Weather condition string from Home Assistant.
 * @return const char* Weather icon string.
 */
inline const char *weatherGlyph(const std::string &condition)
{
    /**< Clear */
    if (condition == "sunny")
        return "\U000F0599";   /**< mdi-weather-sunny */

    if (condition == "clear-night")
        return "\U000F0594";   /**< mdi-weather-night */

    /**< Clouds */
    if (condition == "partlycloudy")
        return "\U000F0595";   /**< mdi-weather-partly-cloudy */

    if (condition == "cloudy")
        return "\U000F0590";   /**< mdi-weather-cloudy */

    /**< Rain */
    if (condition == "rainy")
        return "\U000F0597";   /**< mdi-weather-rainy */

    if (condition == "pouring")
        return "\U000F0596";   /**< mdi-weather-pouring */

    /**< Storm */
    if (condition == "lightning")
        return "\U000F0593";   /**< mdi-weather-lightning */

    if (condition == "lightning-rainy")
        return "\U000F067E";   /**< mdi-weather-lightning-rainy */

    /**< Snow */
    if (condition == "snowy")
        return "\U000F0F36";   /**< mdi-weather-snowy */

    if (condition == "snowy-rainy")
        return "\U000F067F";   /**< mdi-weather-snowy-rainy */

    /**< Atmosphere */
    if (condition == "fog")
        return "\U000F0591";   /**< mdi-weather-fog */

    if (condition == "hail")
        return "\U000F0592";   /**< mdi-weather-hail */

    /**< Wind */ 
    if (condition == "windy")
        return "\U000F059D";   /**< mdi-weather-windy */

    if (condition == "windy-variant")
        return "\U000F059E";   /**< mdi-weather-windy-variant */

    /**< Exceptional */
    if (condition == "exceptional")
        return "\U000F0F2F";   /**< mdi-weather-cloudy-alert */

    /**< Default */
    return "\U000F0590";       /**< Cloudy */
}

/**
 * @brief Function to return weather icon color from condition string.
 * 
 * @param condition Weather condition string from Home Assistant.
 * @return esphome::Color Color to show the icon, Black or Red.
 */
inline esphome::Color weatherColor(const std::string &condition)
{
    if (condition == "sunny")
        return esphome::Color(255,0,0);

    if (condition == "lightning")
        return esphome::Color(255,0,0);

    if (condition == "lightning-rainy")
        return esphome::Color(255,0,0);

    if (condition == "exceptional")
        return esphome::Color(255,0,0);

    return esphome::Color(0,0,0);
}