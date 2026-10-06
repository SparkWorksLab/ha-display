

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
    else if (int(id(iaq).state) >= 51 && int(id(iaq).state) <= 100) {          
        glyph = "\U000F0513";
    }
    else if (int(id(iaq).state) >= 101 && int(id(iaq).state) <= 150) {    
        glyph = "\U000F0514";
    }
    else if (int(id(iaq).state) >= 151 && int(id(iaq).state) <= 200) {
        glyph = "\U000F0512";
    }
    else if (int(id(iaq).state) >= 201 && int(id(iaq).state) <= 250) {
        glyph = "\U000F0511";
    }
    else if (int(id(iaq).state) >= 251 && int(id(iaq).state) <= 350) {
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

    it.printf(
        L1_MIDDLE_X / 2,        
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y4,
        font_16,
        COLOR_BLACK,
        esphome::display::TextAlign::TOP_CENTER,
        "VOC: %.1f",
        id(VOC_sensor).state);

    it.printf(
        L1_MIDDLE_X / 2,        
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y5,
        font_16,
        COLOR_BLACK,
        esphome::display::TextAlign::TOP_CENTER,
        "CO2: %.0f",
        id(CO2_sensor).state); 

    it.printf(
        L1_MIDDLE_X / 2,        
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y6,
        font_16,
        COLOR_BLACK,
        esphome::display::TextAlign::TOP_CENTER,
        "P: %.0fhPa",
        id(pressure_sensor).state);   

    it.printf(
        L1_MIDDLE_X * 1.5,
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y2,
        font_26,
        COLOR_BLACK,
        esphome::display::TextAlign::TOP_CENTER,
        "%.1f°",
        id(temperature_sensor).state); 

    it.printf(
        L1_MIDDLE_X * 1.5,        
        L1_HEADER_Y + L1_WIDGET_Y + L1_MIDDLE_OFFSET_Y3,
        font_26,
        COLOR_BLACK,
        esphome::display::TextAlign::TOP_CENTER,
        "%.1f%%",
        id(humidity_sensor).state); 
}
