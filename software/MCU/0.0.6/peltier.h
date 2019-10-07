#define peltier_h

#include "Arduino.h"


/*    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/
class peltier {

  public:
  void createPeltier(uint8_t A,uint8_t B,uint8_t E, uint8_t pwm);
  void coolFast();
   void heatFast();
    bool cool(bool activate, uint8_t pwmValue);
     bool heat(bool activate, uint8_t pwmValue);
      bool powerOff(bool confirm);

  private:
    uint8_t vectorPin[6];
};
