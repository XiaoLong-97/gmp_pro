
#ifndef _FILE_INTERFACE_BASE_HPP_
#define _FILE_INTERFACE_BASE_HPP_


// Controller will use value to implement controller.
template<typename T>
class channel_base
{
    // for ADC: output result (after scaled, and biased)
    // for DAC: output analog (per unit value)
    // for PWM: compare target (per unit value)
    //
    // Note: T may be single channel or dual channel even quads.
    T value;
};


#endif // _FILE_INTERFACE_BASE_HPP_
