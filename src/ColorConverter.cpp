#include "ColorConverter.h"
#include "Settings.h"
#include <random>

sf::Color ColorConverter::HSVtoRGB(float hue, float saturation, float value)
{
    
    int hi = static_cast<int>(std::floor(hue / 60.0f)) % 6;
    float f = (hue / 60.0f) - static_cast<float>(hi);

    float p = value * (1.0f - saturation);
    float q = value * (1.0f - (f * saturation));
    float t = value * (1.0f - ((1.0f - f) * saturation));

    float r, g, b;

    switch (hi) {
    case 0:
        r = value;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = value;
        b = p;
        break;
    case 2:
        r = p;
        g = value;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = value;
        break;
    case 4:
        r = t;
        g = p;
        b = value;
        break;
    case 5:
    default:
        r = value;
        g = p;
        b = q;
        break;
    }

    return sf::Color(static_cast<sf::Uint8>(r * 255), static_cast<sf::Uint8>(g * 255), static_cast<sf::Uint8>(b * 255));
}

sf::Color ColorConverter::getRandomColor()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 360.0f);
    std::uniform_real_distribution<float> dis1(0.0f, 1.0f);
    std::uniform_real_distribution<float> dis2(0.0f, 1.0f);
    float hue = dis(gen);
    float sat = dis1(gen);
    float val = dis2(gen);
    sf::Color randCol(hue, sat, val);
    return randCol;
}

sf::Color ColorConverter::RGBtoHSV(sf::Color color)
{
    float r = static_cast<float>(color.r) / 255.0f;
    float g = static_cast<float>(color.g) / 255.0f;
    float b = static_cast<float>(color.b) / 255.0f;

    float maxComponent = std::max(std::max(r, g), b);
    float minComponent = std::min(std::min(r, g), b);

    float hue, saturation, value;

    // Calculate the hue
    if (maxComponent == minComponent) {
        hue = 0.0f; // No saturation, so hue is undefined
    }
    else if (maxComponent == r) {
        hue = 60.0f * ((g - b) / (maxComponent - minComponent));
    }
    else if (maxComponent == g) {
        hue = 120.0f + 60.0f * ((b - r) / (maxComponent - minComponent));
    }
    else {
        hue = 240.0f + 60.0f * ((r - g) / (maxComponent - minComponent));
    }

    if (hue < 0.0f) {
        hue += 360.0f;
    }

    // Calculate the saturation
    if (maxComponent == 0.0f) {
        saturation = 0.0f;
    }
    else {
        saturation = 1.0f - (minComponent / maxComponent);
    }

    // Calculate the value
    value = maxComponent;

    return sf::Color(hue, saturation * 255.0f, value * 255.0f);
}
