#include "FPSCounter.h"
sf::Clock FPSCounter::_clock;
sf::Text FPSCounter::_objectsText;
sf::Text FPSCounter::_fpsText;
int FPSCounter::_frameCounter=0;
float FPSCounter::_deltaFrames=20.0f;
int FPSCounter::_frameCounter1=0;
float FPSCounter::_deltaFrames1=20.0f;
int FPSCounter::_hue=0;
float FPSCounter::_sat=0.0f;
float FPSCounter::_val=1.0f;
int FPSCounter::_colorTransitionSpeed = 100.0f;

void FPSCounter::init(float x, float y, float z, float w, sf::Font* font)
{
	_fpsText.setFont(*font);
	_objectsText.setFont(*font);
	_fpsText.setPosition(x, y);
	_objectsText.setPosition(z, w);
	_fpsText.setCharacterSize(20);
	_objectsText.setCharacterSize(20);
	sf::Color color(HSVtoRGB(_hue, _sat, _val));
	_fpsText.setFillColor(color);
	_objectsText.setFillColor(color);
}


void FPSCounter::update(float deltaTime)
{	
	_frameCounter++;
	if (_frameCounter == _deltaFrames) 
	{
		_frameCounter = 0;
		// restarting the timer

		sf::Time elapsed = _clock.restart();
		int fps = _deltaFrames / elapsed.asSeconds();
		_fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
		updateColor(fps, deltaTime);
	}
}

void FPSCounter::displayOjbectCount(int _objCount)
{
	_frameCounter1++;
	if (_frameCounter1 == _deltaFrames1)
	{
		_frameCounter1 = 0;
		int objCount = _objCount;
		_objectsText.setString("OBJECTS COUNT: " + std::to_string(static_cast<int>(objCount)));
	}
}

void FPSCounter::updateColor(float fps, float deltaTime)
{	
	if (_sat < 1.0f) 
	{
		_sat += 2.5f * deltaTime;
	}
	if (fps < 30.0f) 
	{
		if (_hue > 0) 
		{
			_hue -= std::ceil(_colorTransitionSpeed * deltaTime);
		}
		normalizeHSV();
		sf::Color newColor(HSVtoRGB(_hue, _sat, _val));
		_fpsText.setFillColor(newColor);
	}
	else if (fps > 30.0f && fps < 60.0f) 
	{
		if (_hue > 30)
		{
			_hue -= std::ceil(_colorTransitionSpeed * deltaTime);
		}
		else if (_hue < 30)
		{
			_hue += std::ceil(_colorTransitionSpeed * deltaTime);
		}
		normalizeHSV();
		sf::Color newColor(HSVtoRGB(_hue, _sat, _val));
		_fpsText.setFillColor(newColor);
	}
	else if (fps > 60.0f && fps < 130.0f) 
	{
		if (_hue > 60)
		{
			_hue -= std::ceil(_colorTransitionSpeed * deltaTime);
		}
		else if (_hue < 60)
		{
			_hue += std::ceil(_colorTransitionSpeed * deltaTime);
		}
		normalizeHSV();
		sf::Color newColor(HSVtoRGB(_hue, _sat, _val));
		_fpsText.setFillColor(newColor);
	}
	else if (fps > 130.0f)
	{
		if (_hue > 120)
		{
			_hue -= std::ceil(_colorTransitionSpeed * deltaTime);
		}
		else if (_hue < 120)
		{
			_hue += std::ceil(_colorTransitionSpeed * deltaTime);
		}
		normalizeHSV();
		sf::Color newColor(HSVtoRGB(_hue, _sat, _val));
		_fpsText.setFillColor(newColor);
	}	
}

void FPSCounter::normalizeHSV()
{
	if (_hue > 360)
	{
		_hue -= 360;
	}
	if (_sat > 1.0f)
	{
		_sat = 1.0f;
	}
	else if (_sat < 0.0f)
	{
		_sat = 0.0f;
	}
	if (_val > 1.0f)
	{
		_val = 1.0f;
	}
	else if (_val < 0.0f)
	{
		_val = 0.0f;
	}
}

void FPSCounter::draw(sf::RenderWindow* window)
{
	window->draw(_fpsText);
	window->draw(_objectsText);
}
sf::Color FPSCounter::HSVtoRGB(float h, float s, float v) 
{
	int hi = static_cast<int>(h / 60) % 6;
	float f = h / 60 - std::floor(h / 60);
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);
	switch (hi) {
	case 0: return sf::Color(static_cast<sf::Uint8>(v * 255), static_cast<sf::Uint8>(t * 255), static_cast<sf::Uint8>(p * 255));
	case 1: return sf::Color(static_cast<sf::Uint8>(q * 255), static_cast<sf::Uint8>(v * 255), static_cast<sf::Uint8>(p * 255));
	case 2: return sf::Color(static_cast<sf::Uint8>(p * 255), static_cast<sf::Uint8>(v * 255), static_cast<sf::Uint8>(t * 255));
	case 3: return sf::Color(static_cast<sf::Uint8>(p * 255), static_cast<sf::Uint8>(q * 255), static_cast<sf::Uint8>(v * 255));
	case 4: return sf::Color(static_cast<sf::Uint8>(t * 255), static_cast<sf::Uint8>(p * 255), static_cast<sf::Uint8>(v * 255));
	default: return sf::Color(static_cast<sf::Uint8>(v * 255), static_cast<sf::Uint8>(p * 255), static_cast<sf::Uint8>(q * 255));
	}
}
