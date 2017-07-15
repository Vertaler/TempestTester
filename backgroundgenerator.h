#ifndef BACKGROUNDGENERATOR_H
#define BACKGROUNDGENERATOR_H

#include <QBrush>
enum FillingType{
    RGB,
    RANDOM,
    WHITE
};

class BackgroundGenerator
{
private:
    const int RED_COLOR = 0xFF0000FF;
    const int GREEN_COLOR = 0x00FF00FF;
    const int BLUE_COLOR = 0x0000FFFF;

    int randColor();
    void setPixel(uchar* bytes, int index, int pixelColor);
    QBrush randomLinesBackground(int width, int height, int linesCount, uchar* bytesArray);
    QBrush rgbLinesBackground(int width, int height, int linesCount);
    QBrush whiteLinesBackground(int width, int height, int linesCount);

public:
    BackgroundGenerator();
    QBrush GenerateBackground(int width, int height, int linesCount, FillingType fillingType);
};

#endif // BACKGROUNDGENERATOR_H
