#pragma once
class Settings 
{
public:
	static float getConversionFactor();
	static void setConversionFactor(float convFact);
private:
	static float _conversionFactor;
};