/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

 #include "../../inc/MarlinConfig.h"

 #if ENABLED(LCD_SET_PROGRESS_MANUALLY)
 
 #include "../gcode.h"
 #include "../../lcd/marlinui.h"
 #include "../../sd/cardreader.h"
 
 /**
  * M73: Set percentage complete (for display on LCD)
  *
  * Example:
  *   M73 P25 ; Set progress to 25%
  */
 void GcodeSuite::M73()
 {
   if (serial_connection_active)
   {
     ; // Ignore M73 commands when printing from Octoprint
   }
   else
   {
     if (parser.seenval('P'))
       ui.set_progress((PROGRESS_SCALE) > 1
                           ? parser.value_float() * (PROGRESS_SCALE)
                           : parser.value_byte());
 #if BOTH(LCD_SET_PROGRESS_MANUALLY, USE_M73_REMAINING_TIME)
     if (parser.seenval('R'))
       ui.set_remaining_time(60 * parser.value_ulong());
 #endif
   }
 }
 #endif // LCD_SET_PROGRESS_MANUALLY