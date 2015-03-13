# Simple Embedded C Transfer Protocol #

## Where are needed? ##
  * General purpose. When you need a special protocol between two devices.
  * embedded device to communication smartly with other devices
> > example: light embedded device <> PC

## Main Features ##
  * [fully c-code](http://code.google.com/p/sectp/source/checkout)
  * light and fast
  * input & output FIFO -buffers
  * dynamically memory allocate
  * leakfree
  * [easy to use](http://code.google.com/p/sectp/wiki/WikiHowto)
  * easy to customizations
  * free to use. (if you make modifications, please tell me what it's better way to do some..)
  * use example: usart / USB / SPI / ...


### Message structure ###
|Length|Group|Type|Type extension|Data|
|:-----|:----|:---|:-------------|:---|
| 4b | 1b | 1b | 1b | Nb|

### Message traffic ###
![http://jussiva.dyndns.org/CodeGoogle/sectp/message_transmissions.png](http://jussiva.dyndns.org/CodeGoogle/sectp/message_transmissions.png)




---

This protocol is developed in my Diplom thesis work.
It's quite simple but portable because of C.

## Who can we thank for this? ##
Jussi Vatjus-Anttila @jussiva (at) gmail.com

### Other my open-source projects: ###
