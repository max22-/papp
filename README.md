# A triple stepper motor driver for Atmega328p
* Drives 3 bipolar stepper motors
* Made to work with [GRBL](https://github.com/grbl/grbl) 
* Half step (no full step or micro step, perhaps later)
* Very early phase of development

# Download and burn
* git clone https://github.com/max22-/papp.git
* cd papp
* make
* make install

# Todo
* Verify that no pulse form GRBL is lost (30kHz ?)
* Add support for micro-stepping and full-stepping
* Test it with an arduino board

# Changelog
