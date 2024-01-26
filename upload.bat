avrdude -c arduino -p atmega328p -P COM3 -U flash:w:"ClkMod.hex":a

"C:\Program Files\PuTTY\putty.exe" -serial COM3