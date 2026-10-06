/**
 * @file display_bsec.h
 * @brief E-paper display widget drawing functions.
 *
 * Provides reusable functions for drawing the different widgets displayed
 * on the e-paper dashboard.
 *
 * The widgets include the header, weather forecast, environmental sensor using
 * BSEC2 algorithm, Smart Plug monitoring, room sensors, and battery indicators.
 */

 #pragma once

#include "esphome.h"
#include "esphome/components/display/display.h"
#include "weather_icons.h"
#include "power.h"
#include <cmath>

inline const esphome::Color COLOR_BLACK(0, 0, 0);
inline const esphome::Color COLOR_WHITE(255, 255, 255);
inline const esphome::Color COLOR_RED(255, 0, 0);

/**
 * @brief Draws the outer screen frame.
 * 
 */
inline void drawFrame(
    esphome::display::Display &it)
{
    it.line(0, 0, SCREEN_WIDTH - 1, 0, COLOR_BLACK);
    it.line(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, COLOR_BLACK);
    it.line(0, 0, 0, SCREEN_HEIGHT - 1, COLOR_BLACK);
    it.line(SCREEN_WIDTH - 1, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, COLOR_BLACK);
}

/**
 * @brief Draws the Wi-Fi status icon.
 *
 * @param it Display instance.
 * @param x Horizontal coordinate measured from the bottom-left corner of the icon.
 * @param y Vertical coordinate measured from the bottom-left corner of the icon.
 */
inline void drawWifiStatus(
    esphome::display::Display &it,
    int x,
    int y)
{
    const char *glyph;

    if((id(sleep_time) != (id(ha_sleep_duration).state * 60000)) && (id(ha_display_deep_sleep).state))
    {
        glyph = "\U000F1B94";  /**< Sleep Time */
    }
    else if (!id(wifi_ok))
    {
        glyph = "\U000F05AA";  /**< WiFi not connected */
    }
    else if (!id(ha_ok))
    {
        glyph = "\U000F16B5";  /**< HA not connected */
    }
    else
    {
        glyph = "\U000F05A9";  /**< WiFi & HA OK */
    }

    it.printf(
        x,
        y,
        icon_wifi,
        COLOR_WHITE,
        TextAlign::BOTTOM_LEFT,
        glyph);

    if(!id(ha_display_deep_sleep).state && id(wifi_ok) && id(ha_ok))
    {    
        it.printf(
            x + 25,
            y + 1,
            icon_wifi,
            COLOR_WHITE,
            TextAlign::BOTTOM_LEFT,
            "\U000F04B3");
    }
}

/**
 * @brief Draws the screen header.
 * 
 */
inline void drawHeader(
    esphome::display::Display &it)
{

    auto now = id(ha_time).now();
      
    it.filled_rectangle(1, 1, SCREEN_WIDTH - 2, L1_HEADER_Y - 1, COLOR_RED);
    it.line(1, L1_HEADER_Y - 1, SCREEN_WIDTH - 2, L1_HEADER_Y - 1, COLOR_WHITE);

    it.printf( 
        SCREEN_WIDTH / 2, 
        L1_HEADER_Y - 1, 
        font_16, 
        COLOR_WHITE, 
        TextAlign::BOTTOM_CENTER, 
        "SparkWorks Lab");

    if (now.is_valid())
    {
        it.strftime( 
            5, 
            L1_HEADER_Y - 1, 
            font_16, 
            COLOR_WHITE, 
            TextAlign::BOTTOM_LEFT, 
            "%H:%M", now);
    }
    else
    {
        it.printf( 
            5, 
            L1_HEADER_Y - 1, 
            font_16, 
            COLOR_WHITE, 
            TextAlign::BOTTOM_LEFT, 
            "--:--");
    }
    
    drawWifiStatus(
        it,
        60,
        L1_HEADER_Y - 1);

    drawBatteryHeader(
        it,
        SCREEN_WIDTH - 4,
        L1_HEADER_Y - 1,
        font_16,
        COLOR_WHITE,
        id(battery_voltage).state,
        id(battery_percent).state);  

    /**< Debug for Sleep Time */
    /*it.printf(
        300, 
        L1_HEADER_Y - 1, 
        font_16, 
        COLOR_WHITE, 
        TextAlign::BOTTOM_LEFT, 
        "%u",
        id(sleep_time)/1000);*/
}

/**
 * @brief Draws the widget of a day in the forecast section.
 * 
 * @param x Horizontal coordinate, draw from top left corner of widget.
 * @param y Vertical coordinate, draw from top left corner of widget.
 * @param day Day of the Week.
 * @param tmax Maximum temperature.
 * @param tmin Minimum temperature.
 * @param condition Weather condition.
 */
inline void drawForecastDay(
    esphome::display::Display &it,
    int x,
    int y,
    const char *day,
    float tmax,
    float tmin,
    const char *condition)
{    
    if (std::isnan(tmax) || std::isnan(tmin))
    {
        /**< Print Week Day */
        it.printf(
            x + (L1_TOP_X / 2),
            y + L1_TOP_OFFSET_Y1,
            font_16,
            COLOR_WHITE,
            esphome::display::TextAlign::TOP_CENTER,
            "N/A");   

        /**< Print Weather Icon */
        it.print(
            x + (L1_TOP_X / 2),
            y + L1_TOP_OFFSET_Y2,
            weather_icons,
            weatherColor("exceptional"),
            esphome::display::TextAlign::TOP_CENTER,
            weatherGlyph("exceptional"));  

        /**< Print Max & Min temperatures */
        it.printf(
            x + (L1_TOP_X / 2) + L1_TOP_OFFSET_X3,
            y + L1_TOP_OFFSET_Y3,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "--°/--°"); 
    }
    else
    {  
        /**< Print Week Day */
        it.printf(
            x + (L1_TOP_X / 2),
            y + L1_TOP_OFFSET_Y1,
            font_16,
            COLOR_WHITE,
            esphome::display::TextAlign::TOP_CENTER,
            "%s",
            day);  

        /**< Print Weather Icon */  
        it.print(
            x + (L1_TOP_X / 2),
            y + L1_TOP_OFFSET_Y2,
            weather_icons,
            weatherColor(condition),
            esphome::display::TextAlign::TOP_CENTER,
            weatherGlyph(condition)); 

        /**< Print Max & Min temperatures */
        it.printf(
            x + (L1_TOP_X / 2) + L1_TOP_OFFSET_X3,
            y + L1_TOP_OFFSET_Y3,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.0f°/%.0f°",
            tmax, tmin);  
    }
}

/**
 * @brief Draws the weather forecast section.
 * 
 */
inline void drawForecast(
    esphome::display::Display &it)
{
    it.filled_rectangle(0, L1_HEADER_Y, SCREEN_WIDTH - 1, L1_HEADER_Y, COLOR_BLACK);
    it.line(L1_TOP_X, L1_HEADER_Y, L1_TOP_X, (2 * L1_HEADER_Y) - 1, COLOR_WHITE);
    it.line(2 * L1_TOP_X, L1_HEADER_Y, 2 * L1_TOP_X, (2 * L1_HEADER_Y) - 1, COLOR_WHITE);
    it.line(3 * L1_TOP_X, L1_HEADER_Y, 3 * L1_TOP_X, (2 * L1_HEADER_Y) - 1, COLOR_WHITE);
    it.line(4 * L1_TOP_X, L1_HEADER_Y, 4 * L1_TOP_X, (2 * L1_HEADER_Y) - 1, COLOR_WHITE);
    it.line(L1_TOP_X, 2 * L1_HEADER_Y, L1_TOP_X, L1_HEADER_Y + L1_WIDGET_Y, COLOR_BLACK);
    it.line(2 * L1_TOP_X, 2 * L1_HEADER_Y, 2 * L1_TOP_X, L1_HEADER_Y + L1_WIDGET_Y, COLOR_BLACK);
    it.line(3 * L1_TOP_X, 2 * L1_HEADER_Y, 3 * L1_TOP_X, L1_HEADER_Y + L1_WIDGET_Y, COLOR_BLACK);
    it.line(4 * L1_TOP_X, 2 * L1_HEADER_Y, 4 * L1_TOP_X, L1_HEADER_Y + L1_WIDGET_Y, COLOR_BLACK);

    drawForecastDay(
        it,
        0,
        L1_HEADER_Y,
        id(forecast_day_1).state.c_str(),
        id(forecast_temp_max_1).state,
        id(forecast_temp_min_1).state,
        id(forecast_condition_1).state.c_str()); 

    drawForecastDay(
        it,
        L1_TOP_X,
        L1_HEADER_Y,
        id(forecast_day_2).state.c_str(),
        id(forecast_temp_max_2).state,
        id(forecast_temp_min_2).state,
        id(forecast_condition_2).state.c_str()); 

    drawForecastDay(
        it,
        2 * L1_TOP_X,
        L1_HEADER_Y,
        id(forecast_day_3).state.c_str(),
        id(forecast_temp_max_3).state,
        id(forecast_temp_min_3).state,
        id(forecast_condition_3).state.c_str()); 

    drawForecastDay(
        it,
        3 * L1_TOP_X,
        L1_HEADER_Y,
        id(forecast_day_4).state.c_str(),
        id(forecast_temp_max_4).state,
        id(forecast_temp_min_4).state,
        id(forecast_condition_4).state.c_str()); 

    drawForecastDay(
        it,
        4 * L1_TOP_X,
        L1_HEADER_Y,
        id(forecast_day_5).state.c_str(),
        id(forecast_temp_max_5).state,
        id(forecast_temp_min_5).state,
        id(forecast_condition_5).state.c_str());
}

/**
 * @brief Draws the BME688 sensor widget with BSEC2 algorithm.
 * 
 */
inline void drawAirSensor(
    esphome::display::Display &it)
{
    it.filled_rectangle(0, L1_HEADER_Y + L1_WIDGET_Y, SCREEN_WIDTH - 1, L1_HEADER_Y, COLOR_BLACK);
    it.line(L1_MIDDLE_X * 2, L1_HEADER_Y + L1_WIDGET_Y, L1_MIDDLE_X * 2, (2 * L1_HEADER_Y) + L1_WIDGET_Y + 1, COLOR_WHITE);
    it.line(L1_MIDDLE_X * 2, (2 * L1_HEADER_Y) + L1_WIDGET_Y, L1_MIDDLE_X * 2, L1_HEADER_Y + (2 * L1_WIDGET_Y), COLOR_BLACK);

    it.printf(
        L1_MIDDLE_X - 10,
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y1,
        font_16,
        COLOR_WHITE,
        esphome::display::TextAlign::TOP_CENTER,
        "Air Quality"); 

    const char *glyph;

    if ( int(id(iaq).state) <= 50) {
        glyph = "\U000F0A50";
    }
    else if (int(id(iaq).state) <= 100) {          
        glyph = "\U000F0513";
    }
    else if (int(id(iaq).state) <= 150) {    
        glyph = "\U000F0514";
    }
    else if (int(id(iaq).state) <= 200) {
        glyph = "\U000F0512";
    }
    else if (int(id(iaq).state) <= 250) {
        glyph = "\U000F0511";
    }
    else if (int(id(iaq).state) <= 350) {
        glyph = "\U000F1586";
    }
    else if (int(id(iaq).state) >= 351) {
        glyph = "\U000F0BC6";
    }
    else {
        glyph = "\U000F0028";
    } 

    it.printf(
        L1_MIDDLE_X +60,
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y1,
        icon_iaq,
        COLOR_WHITE,
        esphome::display::TextAlign::TOP_CENTER,
        glyph);     

    if(std::isnan(id(VOC_sensor).state))    
    {
        it.print(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y4,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "VOC: ---");
    }
    else
    {
        it.printf(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y4,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "VOC: %.1f",
            id(VOC_sensor).state);
    }

    if(std::isnan(id(CO2_sensor).state))  
    {
        it.print(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y5,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "CO2: ---");         
    }      
    else
    {
        it.printf(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y5,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "CO2: %.0f",
            id(CO2_sensor).state); 
    }

    if(std::isnan(id(pressure_sensor).state))  
    {
        it.print(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y6,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            " ---hPa");   
    }
    else
    {
        it.printf(
            L1_MIDDLE_X / 2,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y6,
            font_16,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.0fhPa",
            id(pressure_sensor).state);   
    }

    if(std::isnan(id(temperature_sensor).state))
    {
        it.print(
            L1_MIDDLE_X * 1.5,
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y2,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "--.-°");
    }
    else
    {
        it.printf(
            L1_MIDDLE_X * 1.5,
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y2,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.1f°",
            id(temperature_sensor).state); 
    }

    if(std::isnan(id(humidity_sensor).state))
    {
        it.print(
            L1_MIDDLE_X * 1.5,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y3,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "--.-%"); 
    }
    else
    {
        it.printf(
            L1_MIDDLE_X * 1.5,        
            L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y3,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.1f%%",
            id(humidity_sensor).state); 
    }
}

/**
 * @brief Draws a Smart Plug widget.
 *
 * Displays the plug name, ON/OFF state, current and power consumption.
 *
 * @param it Display instance.
 * @param x Horizontal coordinate, draw from top left corner of widget.
 * @param y Vertical coordinate, draw from top left corner of widget.
 * @param name Smart Plug name.
 * @param state Current ON/OFF state.
 * @param current Current consumption in amperes.
 * @param power Power consumption in watts.
 */
inline void drawSmartPlug(
    esphome::display::Display &it,
    int x,
    int y,
    const char *name,
    bool state,
    float current,
    float power)
{
    /**< Smart Plug state */
    it.printf(
        x,
        y + L1_MIDDLE_OFFSET_Y1,
        font_16,
        COLOR_WHITE,
        esphome::display::TextAlign::TOP_CENTER,
        "%s %s",
        name,
        state ? "ON" : "OFF");

    /**< Current */
    if(std::isnan(current))
    {
        it.print(
            x,
            y + L1_MIDDLE_OFFSET_Y2,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "-.-A");
    }
    else
    {
        it.printf(
            x,
            y + L1_MIDDLE_OFFSET_Y2,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.1fA",
            current);
    }

    /**< Power */
    if(std::isnan(power))
    {
        it.print(
            x,
            y + L1_MIDDLE_OFFSET_Y3,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "--W");
    }
    else
    {
        it.printf(
            x,
            y + L1_MIDDLE_OFFSET_Y3,
            font_26,
            COLOR_BLACK,
            esphome::display::TextAlign::TOP_CENTER,
            "%.0fW",
            power);
    }
}

/**
 * @brief Draws the Smart Plug widgets section.
 *
 * Draws the separator and the widgets for P1 and P2.
 */
inline void drawSmartPlugs(
    esphome::display::Display &it)
{
    it.line(L1_MIDDLE_X * 3, L1_HEADER_Y + L1_WIDGET_Y, L1_MIDDLE_X * 3, (2 * L1_HEADER_Y) + L1_WIDGET_Y + 1, COLOR_WHITE);
    it.line(L1_MIDDLE_X * 3, (2 * L1_HEADER_Y) + L1_WIDGET_Y, L1_MIDDLE_X * 3, L1_HEADER_Y + (2 * L1_WIDGET_Y), COLOR_BLACK);

    /**< Widget P1 */
    drawSmartPlug(
        it,
        L1_MIDDLE_X * 2.5,
        L1_HEADER_Y + L1_WIDGET_Y,
        "P1",
        id(p1_state).state,
        id(p1_current).state,
        id(p1_power).state);

    /**< Widget P2 */
    drawSmartPlug(
        it,
        L1_MIDDLE_X * 3.5,
        L1_HEADER_Y + L1_WIDGET_Y,
        "P2",
        id(p2_state).state,
        id(p2_current).state,
        id(p2_power).state);          
}

/**
 * @brief Draws a room sensor widget.
 *
 * Displays the sensor name, temperature, humidity, battery State of Charge,
 * and availability status.
 *
 * @param it Display instance.
 * @param x Horizontal coordinate measured from the top-left corner of the widget.
 * @param y Vertical coordinate measured from the top-left corner of the widget.
 * @param title Widget title.
 * @param temperature Measured temperature.
 * @param humidity Measured relative humidity.
 * @param battery Battery State of Charge as a percentage.
 * @param online Current sensor availability status.
 * @param age Time elapsed since last update in minutes.
 */
inline void drawRoomSensor(
    esphome::display::Display &it,
    int x,
    int y,
    const char *title,
    float temperature,
    float humidity,
    float battery,
    bool online,
    float age)
{
    /**< If sensor offline, red color */
    auto color = online ? COLOR_BLACK : COLOR_RED;

    /**< Title */
    it.print(
        x + (L1_BOTTOM_X / 2),
        y + L1_BOTTOM_OFFSET_Y1,
        font_16,
        COLOR_WHITE,
        TextAlign::TOP_CENTER, 
        title);

    /**< Temperature */
    if (std::isnan(temperature))
    {
        it.print(
            x + (L1_BOTTOM_X / 2) + L1_BOTTOM_OFFSET_X2,
            y + L1_BOTTOM_OFFSET_Y2,
            font_26,
            color,
            TextAlign::TOP_CENTER, 
            "--.-°");
    }
    else
    {
        it.printf(
            x + (L1_BOTTOM_X / 2) + L1_BOTTOM_OFFSET_X2,
            y + L1_BOTTOM_OFFSET_Y2,
            font_26,
            color,
            TextAlign::TOP_CENTER, 
            "%.1f°",
            temperature);
    }

    /**< Humidity */
    if (std::isnan(humidity))
    {
        it.print(
            x + (L1_BOTTOM_X / 2),
            y + L1_BOTTOM_OFFSET_Y3,
            font_26,
            color,
            TextAlign::TOP_CENTER, 
            "--%");
    }
    else
    {
        it.printf(
            x + (L1_BOTTOM_X / 2),
            y + L1_BOTTOM_OFFSET_Y3,
            font_26,
            color,
            TextAlign::TOP_CENTER, 
            "%.0f%%",
            humidity);
    }

    /**< Battery Indicator */
    drawBatteryIcon(
        it,
        x + 12,
        y + L1_WIDGET_Y - 1,
        color,
        battery);
    
    if (std::isnan(age))
    {
        it.print(
            x + L1_BOTTOM_X - 2,
            y + L1_WIDGET_Y,
            font_12,
            color,
            TextAlign::BOTTOM_RIGHT, 
            "--m");
    }
    else
    {
        it.printf(
            x + L1_BOTTOM_X - 2,
            y + L1_WIDGET_Y,
            font_12,
            color,
            TextAlign::BOTTOM_RIGHT, 
            "%.0fm",
            age);
    }
}

/**
 * @brief Function to draw Room Sensors section.
 * 
 * Draws the separator and the widgets for T1-T4 sensors.
 * 
 */
inline void drawRoomSensors(
    esphome::display::Display &it)
{        
    it.filled_rectangle(0, L1_HEADER_Y + (2 * L1_WIDGET_Y), SCREEN_WIDTH - 1, L1_HEADER_Y, COLOR_BLACK);
    it.line(L1_BOTTOM_X, L1_HEADER_Y + (2 * L1_WIDGET_Y), L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y) + 1, COLOR_WHITE);
    it.line(2 * L1_BOTTOM_X, L1_HEADER_Y + (2 * L1_WIDGET_Y), 2 * L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y) + 1, COLOR_WHITE);
    it.line(3 * L1_BOTTOM_X, L1_HEADER_Y + (2 * L1_WIDGET_Y), 3 * L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y) + 1, COLOR_WHITE);
    it.line(L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y), L1_BOTTOM_X, SCREEN_HEIGHT - 1, COLOR_BLACK);
    it.line(2 * L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y), 2 * L1_BOTTOM_X, SCREEN_HEIGHT - 1, COLOR_BLACK);
    it.line(3 * L1_BOTTOM_X, 2 * (L1_HEADER_Y + L1_WIDGET_Y), 3 * L1_BOTTOM_X, SCREEN_HEIGHT - 1, COLOR_BLACK);      
    
    drawRoomSensor(
        it,
        0,
        L1_HEADER_Y + (2 * L1_WIDGET_Y),
        "Living",
        id(t1_temperature).state,
        id(t1_humidity).state,
        id(t1_battery).state,
        id(t1_online).state,
        id(t1_age).state);        
    
    drawRoomSensor(
        it,
        L1_BOTTOM_X,
        L1_HEADER_Y + (2 * L1_WIDGET_Y),
        "Lab",
        id(t2_temperature).state,
        id(t2_humidity).state,
        id(t2_battery).state,
        id(t2_online).state,
        id(t2_age).state);          
    
    drawRoomSensor(
        it,
        2 * L1_BOTTOM_X,
        L1_HEADER_Y + (2 * L1_WIDGET_Y),
        "Bedroom",
        id(t3_temperature).state,
        id(t3_humidity).state,
        id(t3_battery).state,
        id(t3_online).state,
        id(t3_age).state);           
    
    drawRoomSensor(
        it,
        3 * L1_BOTTOM_X,
        L1_HEADER_Y + (2 * L1_WIDGET_Y),
        "Outside",
        id(t4_temperature).state,
        id(t4_humidity).state,
        id(t4_battery).state,
        id(t4_online).state,
        id(t4_age).state);   
}