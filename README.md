# TouchBoard-to-Arduino
This repo shows, how to get data from the touch board of bareconductive to the an arduino, understanding it and sending OSC messages to work with them further.

## Context
To give a bit more context, I created this code in order to create a media art installation at the Generate25 festival.
The installation consisted of three touchpoints attached to the handrail of stairs. 
Ahead of the stairs, we showed a simple touch designer visual which would change, depending which and how many of the touchpoints were touched. 
The goal was to create a mostly wireless installation, to make it look as clean as possible.

We fitted the arduino with a powerbank, to supply power, connected the touchboard to the arduino. 
On three of the sensitives areas of the touchboard we connected wires, to run along the underside of the handrail and connect the touchboard to the touchpoints.
All of our electronics were fit into an electrical box that we attached to the wall below the handrail.
If one of the touchpoints was touched, the arduino sent OSC messages over WiFi to our laptop, which then changed the visuals on screen.
We even created our own WiFi network, using another arduino, to be WiFi independent, since we didn't know the capabilities at the venue.

