# bitconcat

bitwise concatonation helper functions

2 types of functions is provided: one taking unsigned integers and the other taking bools (or whatever can be evaluated in a boolean context)

simple example:

uint8_t lowbits = 0x0a;
uint8_t highbits = 0x0b;

uint16_t result = bitcont_u16(highbits, lowbits);

