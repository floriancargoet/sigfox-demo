#Sigfox Demo

##Purpose

Live demo of communication over Sigfox network

We'll send a colour code (RGB) over Sigfox, and upon reception, our webpage background will change. That's it.

##What

###Hardware

* A breadboard
* A Sigfox modem ([TD 1208](https://github.com/Telecom-Design/Documentation_TD_RF_Module))
* An ATMEGA
* A flex sensor ([Looks like that](http://www.digikey.com/us/en/ph/SpectraSymbol/flex_sensor.html))
* A LED
* A button
* Wires
* Resistors
* Duct tape


![Front view](https://s3-eu-west-1.amazonaws.com/parishackers-resources/2014-10-10+17.39.29.jpg)

![Rear view](https://s3-eu-west-1.amazonaws.com/parishackers-resources/2014-10-10+17.38.37.jpg)





##How

###Embed Software

When the button is pressed, capture the flex sensor value, and map it to an 8-bit value.

First captured measure will be the red component of the colour, second will be the green and third the blue one.

Fourth press on the button will trigger the emission of a short message over Sigfox, containing the colour value

*Arduino code is [here](https://github.com/floriancargoet/sigfox-demo/blob/master/arduino/sigfox_demo/sigfox_demo.ino)*


###Backend

A callback is set on the Sigfox cloud platform.  
It will basically forward the message content to an [heroku-hosted](https://github.com/floriancargoet/sigfox-demo/blob/master/server/server.js) application

```
[POST] https://demo-sigfox.herokuapp.com/sigfox?data={data}
```

###Web page

[The web page](https://github.com/floriancargoet/sigfox-demo/blob/master/server/public/index.html) will poll the server to get the latest received value.  
This value will be used as the background colour of the page
