#include "backgroundgenerator.h"
#include <cstdlib>
#include <ctime>

int BackgroundGenerator::randColor()
{
    srand(time(NULL));

    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    int result = 255;
    result += blue << 8;
    result += green << 16;
    result += red << 24;

    return result;
}

void BackgroundGenerator::setPixel(uchar *bytes, int index, int pixelColor)
{
    bytes[4*index] = pixelColor >> 24;
    bytes[4*index +1]  = pixelColor >> 16;
    bytes[4*index + 2] = pixelColor >> 8;
    bytes[4*index + 3] = pixelColor;
}

QBrush BackgroundGenerator::randomLinesBackground(int width, int height, int linesCount, uchar *bytesArray)
{
    if(linesCount){
        int linesWidth = height / (2*linesCount);
        int currentLine =0;
        do{
            for(int i=0; i< width; i++){
                setPixel(bytesArray, currentLine*width+i, rand()*rand());
            }
            currentLine++;
            if(!(currentLine % linesWidth)){
                currentLine += linesWidth;
            }
        } while(currentLine < height);
    } else{
        int limit = height * width;
        for(int i=0 ; i< limit; i++){
            setPixel(bytesArray, i, rand()* rand());
        }
    }
    QImage result (bytesArray,width, height, QImage::Format_RGBA8888);
    return QBrush(result);
}

BackgroundGenerator::BackgroundGenerator()
{

}

QBrush BackgroundGenerator::GenerateBackground(int width, int height, int linesCount, FillingType fillingType)
{
    int len = 4*width*height;
    uchar* byteArray = new uchar[len];

    for(int i=3; i< len; i+=4){
        byteArray[i] = 255;
    }

    switch (fillingType) {
    case RGB:
        break;
    case RANDOM:
        return randomLinesBackground(width, height, linesCount, byteArray);
        break;
    case WHITE:
        break;
    default:
        break;
    }
    return  QBrush(Qt::black);
}

