/**
 * @file layout.h
 * @brief Display layout definitions and positioning constants.
 *
 * Defines screen dimensions, widget positions, offsets, margins, and other
 * layout-related constants used by the display drawing functions.
 *
 * Keeping layout definitions separate from the drawing code makes it easier
 * to modify the display arrangement without changing widget implementations.
 */

/**< Screen */
constexpr int SCREEN_WIDTH = 400;
constexpr int SCREEN_HEIGHT = 300;

/**< Header */
constexpr int L1_HEADER_Y = 22;                /**< Header height in px */
constexpr int L1_WIDGET_Y = 93;                /**< Header height in px */

/**< Top Section */
constexpr int L1_TOP_X = 80;                   /**< Top section field width in px */
constexpr int L1_TOP_Y = 93;                   /**< Top section field height in px */
constexpr int L1_TOP_OFFSET_X3 = 2;            /**< Top section Line 3 horizontal offset in px */
constexpr int L1_TOP_OFFSET_Y1 = 0;            /**< Top section Line 1 vertical offset in px */
constexpr int L1_TOP_OFFSET_Y2 = 26;           /**< Top section Line 2 vertical offset in px */
constexpr int L1_TOP_OFFSET_Y3 = 67;           /**< Top section Line 3 vertical offset in px */

/**< Middle Section */
constexpr int L1_MIDDLE_X = 100;               /**< Middle section field width in px */
constexpr int L1_MIDDLE_Y = 93;                /**< Middle section field height in px */
constexpr int L1_MIDDLE_OFFSET_Y1 = 0;         /**< Middle section Line 1 vertical offset in px */
constexpr int L1_MIDDLE_OFFSET_Y2 = 25;        /**< Middle section Line 2 vertical offset in px */
constexpr int L1_MIDDLE_OFFSET_Y3 = 55;        /**< Middle section Line 3 vertical offset in px */
constexpr int L1_MIDDLE_OFFSET_Y4 = 27;        /**< Middle section Line 4 vertical offset in px */
constexpr int L1_MIDDLE_OFFSET_Y5 = 47;        /**< Middle section Line 5 vertical offset in px */
constexpr int L1_MIDDLE_OFFSET_Y6 = 67;        /**< Middle section Line 6 vertical offset in px */

/**< Bottom Section */
constexpr int L1_BOTTOM_X = 100;              /**< Bottom section field width in px */
constexpr int L1_BOTTOM_Y = 93;               /**< Bottom section field heigth in px */
constexpr int L1_BOTTOM_OFFSET_X2 = 2;        /**< Bottom section Line 2 horizontal offset in px */
constexpr int L1_BOTTOM_OFFSET_Y1 = 0;        /**< Bottom section Line 1 vertical offset in px */
constexpr int L1_BOTTOM_OFFSET_Y2 = 25;       /**< Bottom section Line 2 vertical offset in px */
constexpr int L1_BOTTOM_OFFSET_Y3 = 55;       /**< Bottom section Line 3 vertical offset in px */
