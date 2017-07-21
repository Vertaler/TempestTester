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

QBrush BackgroundGenerator::generateBackground(int width, int height, int linesCount, uchar *bytesArray, int (*drawPixel) ())
{

    if(linesCount){
        int linesWidth = height / (2*linesCount);
        int currentLine = 0;
        do{
            for(int i=0; i< width; i++){
                setPixel(bytesArray, currentLine*width+i, drawPixel());
            }
            currentLine++;
            if(!(currentLine % linesWidth)){
                currentLine += linesWidth;
            }
        } while(currentLine < height);
    } else{
        int limit = height * width;
        for(int i=0 ; i< limit; i++){
            setPixel(bytesArray, i, drawPixel());
        }
    }
    QImage result (bytesArray,width, height, QImage::Format_RGBA8888);
    return QBrush(result);
}



BackgroundGenerator::BackgroundGenerator()
{

}

QBrush BackgroundGenerator::GenerateBackground(uchar *dataArray, int width, int height, int linesCount, FillingType fillingType)
{
    srand(time(NULL));
    int len = 4*width*height;
    //uchar* byteArray = new uchar[len];

    for(int i=0; i< len; i++){
        dataArray[i] = (i%4 == 3) ? 255: 0;
    }

    QBrush result;

    switch (fillingType) {
    case RANDOM:
        result = generateBackground(width, height, linesCount, dataArray, []() -> int{ return rand()*rand()*rand();});
        break;
    case WHITE:
        result = generateBackground(width, height, linesCount, dataArray, []() -> int {return 0xEEEEEEFF;});
        break;
    default:
        break;
    }
    //delete[] byteArray;
    return result;
}

