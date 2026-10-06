/**
 * @file battery.h
 * @brief Battery monitoring and State of Charge estimation helpers.
 *
 * Provides helper functions for estimating the State of Charge of a Li-Ion
 * battery from its measured voltage.
 *
 * The estimation is based on a voltage lookup table with linear interpolation
 * between adjacent points.
 */

#pragma once

#include "esphome.h"
#include <cmath>

/**< Struct to magnage SoC Look Up Table */
struct BatteryPoint {
    float voltage;
    float percent;
};

/**< Battery percentage Look Up Table */
const BatteryPoint BATTERY_LUT[] = {
    {4.10, 100},
    {4.05, 95},
    {4.00, 90},
    {3.95, 85},
    {3.90, 80},
    {3.85, 75},
    {3.80, 65},
    {3.75, 60},
    {3.70, 55},
    {3.65, 53},
    {3.60, 50},
    {3.55, 45},
    {3.50, 40},
    {3.45, 35},
    {3.40, 30},
    {3.35, 25},
    {3.30, 20},
    {3.25, 12},
    {3.20, 8},
    {3.15, 4},
    {3.10, 2},
    {3.00, 0},
};

/**
 * @brief Function to return battery SoC from LUT.
 * 
 * @param voltage battery voltage.
 * @return float percentage.
 */
inline float batteryPercent(float voltage)
{
    if (std::isnan(voltage))
        return NAN;

    /**< Voltage above/below LUT values */
    if (voltage >= BATTERY_LUT[0].voltage)
        return 100.0f;

    const int count = sizeof(BATTERY_LUT) / sizeof(BATTERY_LUT[0]);

    if (voltage <= BATTERY_LUT[count - 1].voltage)
        return 0.0f;

    /**< Look for interval */
    for (int i = 0; i < count - 1; i++)
    {
        float v_high = BATTERY_LUT[i].voltage;
        float v_low  = BATTERY_LUT[i + 1].voltage;

        if (voltage <= v_high && voltage >= v_low)
        {
            float p_high = BATTERY_LUT[i].percent;
            float p_low  = BATTERY_LUT[i + 1].percent;

            return p_low +
                   (voltage - v_low) *
                   (p_high - p_low) /
                   (v_high - v_low);
        }
    }

    return 0.0f;
}

/**
 * @brief Function to draw battery icon.
 * 
 * @param x Horizontal coordinate, draw from bottom right corner of icon.
 * @param y Vertical coordinate, draw from bottom right corner of icon.
 * @param color Color to draw the icon.
 * @param percent Battery SoC to fill the icon accordingly [0, 100].
 */
inline void drawBatteryIcon(
    esphome::display::Display &it,
    int x,
    int y,
    esphome::Color color,
    float percent)
{

    /**< Draw Battery icon */
    it.rectangle(x - 10, y - 17, 10, 15, color);
    it.rectangle(x - 9, y - 16, 8, 13, color);
    it.rectangle(x - 7, y - 19, 4, 2, color);

    if(percent > 0)
    {
        it.filled_rectangle(x - 8, y - 3 - (percent / 9), 6, (percent / 9), color);
    }
}

/**
 * @brief Function to draw Battery SoC and icon in the header.
 * 
 * @param x Horizontal coordinate, draw from bottom right corner of icon.
 * @param y Vertical coordinate, draw from bottom right corner of icon.
 * @param font Desired font.
 * @param color Color to draw the icon.
 * @param voltage Battery voltage.
 * @param percent Battery SoC to fill the icon accordingly [0, 100].
 */
inline void drawBatteryHeader(
    esphome::display::Display &it,
    int x,
    int y,
    esphome::display::BaseFont *font,
    esphome::Color color,
    float voltage,
    float percent)
{   
    drawBatteryIcon(
        it,
        x,
        y,
        color,
        percent);

    /**< Invalid reading */
    if (std::isnan(voltage) || std::isnan(percent))
    {
        it.print(
            x-12,
            y-1,
            font,
            color,
            TextAlign::BOTTOM_RIGHT,
            "--%");
        return;
    }

    it.printf(
        x-14,
        y,
        font,
        color,
        TextAlign::BOTTOM_RIGHT,
        "%.0f%%",
        percent);
}
