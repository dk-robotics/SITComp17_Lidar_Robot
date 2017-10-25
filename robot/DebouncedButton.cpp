#include "DebouncedButton.h"

DebouncedButton::DebouncedButton(uint8_t pin)
        : time(-1), mode(single), pin(pin), state(false), toggled(false) {
	pinMode(pin, INPUT_PULLUP);
}

void DebouncedButton::setMode(Mode mode) {
	this->mode = mode;
}

boolean DebouncedButton::getDebounced() {
	int in = digitalRead(pin);
    if(in != state && (millis() - time > DEBOUNCE_DELAY || time == -1)) {
        state = (bool) in;
        time = millis();
    }
    return !state;
}

boolean DebouncedButton::getState() {
	switch(mode) {
		case Mode::noDebounce:
			return !digitalRead(pin);
		case Mode::hold:
			return getDebounced();
		case Mode::single:
			boolean oldState = state;
			return getDebounced() && state != oldState;
		case Mode::toggle:
			if(getDebounced())
				toggled = !toggled;
			return toggled;
	}
    return false;
}