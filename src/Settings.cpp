#include "Settings.h"
float Settings::_conversionFactor = 1.0f;

float Settings::getConversionFactor()
{
    return _conversionFactor;
}

void Settings::setConversionFactor(float convFact)
{
    _conversionFactor = convFact;
}

