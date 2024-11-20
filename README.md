# Wake-On-Lan relay

I installed this on a ESP32 chip. Not sure where you can or cannot do it.  
I tried to set power saving settings, finding the weirdest bug where my pc would run out of power to boot and stay neither on nor off due to the fact that this is directly plugged to the pc motherboard and would mess with the voltage. That's my theory anyway. Pretty sure it is possible to do something like `WiFi.setSleep(WIFI_PS_MAX_MODEM)` with or without the need to reset it to NONE before sending the package

## TODO: make an actual readme
