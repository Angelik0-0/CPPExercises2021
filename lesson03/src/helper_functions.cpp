#include "helper_functions.h"

#include <libutils/rasserts.h>


class n;

cv::Mat makeAllBlackPixelsBlue(cv::Mat image) {
//    // TODO реализуйте функцию которая каждый черный пиксель картинки сделает синим
//
//    // ниже приведен пример как узнать цвет отдельного пикселя - состоящий из тройки чисел BGR (Blue Green Red)
//    // чем больше значение одного из трех чисел - тем насыщеннее его оттенок
//    // всего их диапазон значений - от 0 до 255 включительно
//    // т.е. один байт, поэтому мы используем ниже тип unsigned char - целое однобайтовое неотрицательное число
//    cv::Vec3b color = image.at<cv::Vec3b>(13, 5); // взяли и узнали что за цвет в пикселе в 14-ом ряду (т.к. индексация с нуля) и 6-ой колонке
//    unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
//    unsigned char green = color[1];
//    unsigned char red = color[2];
//
//    // как получить белый цвет? как получить черный цвет? как получить желтый цвет?
//    // поэкспериментируйте! например можете всю картинку заполнить каким-то одним цветом
//
//    // пример как заменить цвет по тем же координатам
//    // red = 0;
//    // запустите эту версию функции и посмотрите на получившуюся картинку - lesson03/resultsData/01_blue_unicorn.jpg
//    // какой пиксель изменился? почему он не чисто красный?
//    image.at<cv::Vec3b>(13, 5) = cv::Vec3b(blue, green, red);
//
//    return image;

    for(int i=0; i<101; ++i){
        for(int j=0; j<101; ++j){
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
            unsigned char green = color[1];
            unsigned char red = color[2];
            if(blue <= 5 && green <= 5 && red <= 5){
                blue = 255;
                green = 0;
                red = 0;
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(blue, green, red);
            }
        }
    }


    return image;
}

cv::Mat invertImageColors(cv::Mat image) {
    // TODO реализуйте функцию которая каждый цвет картинки инвертирует:
    // т.е. пусть ночь станет днем, а сумрак рассеется
    // иначе говоря замените каждое значение яркости x на (255-x) (т.к находится в диапазоне от 0 до 255)
    for(int i=0; i<101; ++i){
        for(int j=0; j<101; ++j){
            cv::Vec3b color = image.at<cv::Vec3b>(i, j);
            unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
            unsigned char green = color[1];
            unsigned char red = color[2];

            blue = 255-blue;
            green = 255-green;
            red = 255-red;

            image.at<cv::Vec3b>(i, j) = cv::Vec3b(blue, green, red);
        }
    }
    return image;
}

cv::Mat addBackgroundInsteadOfBlackPixels(cv::Mat object, cv::Mat background) {
    // TODO реализуйте функцию которая все черные пиксели картинки-объекта заменяет на пиксели с картинки-фона
    // т.е. что-то вроде накладного фона получится

    // гарантируется что размеры картинок совпадают - проверьте это через rassert, вот например сверка ширины:
    rassert(object.cols == background.cols, 341241251251351);
    rassert(object.rows == background.rows, 87697656853457);

    for(int i=0; i<101; ++i){
        for(int j=0; j<101; ++j){
            cv::Vec3b color0 = object.at<cv::Vec3b>(i, j);
            unsigned char blue0 = color0[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
            unsigned char green0 = color0[1];
            unsigned char red0 = color0[2];
            if(blue0 <= 5 && green0 <= 5 && red0 <= 5){
                cv::Vec3b color = background.at<cv::Vec3b>(i, j);
                unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
                unsigned char green = color[1];
                unsigned char red = color[2];
                object.at<cv::Vec3b>(i, j) = cv::Vec3b(blue, green, red);
            }

        }
    }

    return object;
}

cv::Mat addBackgroundInsteadOfBlackPixelsLargeBackground(cv::Mat object, cv::Mat largeBackground) {
    // теперь вам гарантируется что largeBackground гораздо больше - добавьте проверок этого инварианта (rassert-ов)
    rassert(object.cols <= largeBackground.cols, 341241251251351);
    rassert(object.rows <= largeBackground.rows, 87697656853457);
    // TODO реализуйте функцию так, чтобы нарисовался объект ровно по центру на данном фоне, при этом черные пиксели объекта не должны быть нарисованы
    int a = object.rows;
    int b = object.cols;
    int c = largeBackground.rows;
    int d = largeBackground.cols;
    for(int i=0; i<a;++i){
        for(int j=0; j<b; ++j){
            cv::Vec3b color = object.at<cv::Vec3b>(i, j);
            unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
            unsigned char green = color[1];
            unsigned char red = color[2];
            if(blue < 5 && green < 5 && red < 5){

            } else {
                cv::Vec3b color2 = object.at<cv::Vec3b>(i,j);
                unsigned char blue2 = color[0];
                unsigned char green2 = color[1];
                unsigned char red2 = color[2];
                largeBackground.at<cv::Vec3b>(i+(c-a)/2,j+(d-b)/2) = cv::Vec3b(blue2, green2, red2);
            }
        }
    }
//    for(int i = (c-a)/2; i < c - (c-a)/2; ++i){
//        for(int j = (d-b)/2; j < d - (d-b)/2; ++j){

    return largeBackground;
}


cv::Mat unicornsOtake(cv::Mat object, cv::Mat largeBackground, int n){
    rassert(object.cols <= largeBackground.cols, 3414151251351);
    rassert(object.rows <= largeBackground.rows, 876765853457);
    int a = object.rows;
    int b = object.cols;
    int c = largeBackground.rows;
    int d = largeBackground.cols;
    while(n>0){
        n--;
        int k = rand() % (c-a);
        int l = rand() % (d-b);
        for(int i = 0; i < a; ++i){
            for(int j = 0; j < b; ++j){
                cv::Vec3b color = object.at<cv::Vec3b>(i, j);
                unsigned char blue = color[0]; // если это число равно 255 - в пикселе много синего, если равно 0 - в пикселе нет синего
                unsigned char green = color[1];
                unsigned char red = color[2];
                if(blue < 5 && green < 5 && red < 5){

                } else {
                    cv::Vec3b color2 = object.at<cv::Vec3b>(i,j);
                    unsigned char blue2 = color[0];
                    unsigned char green2 = color[1];
                    unsigned char red2 = color[2];
                    largeBackground.at<cv::Vec3b>(i+k,j+l) = cv::Vec3b(blue2, green2, red2);
                }
            }
        }
    }
    return largeBackground;

}

cv::Mat bigUnicorn(cv::Mat object, cv::Mat largeBackground){
    rassert(object.cols <= largeBackground.cols, 341415251351);
    rassert(object.rows <= largeBackground.rows, 87676553457);
    int a = object.rows;
    int b = object.cols;
    int c = largeBackground.rows;
    int d = largeBackground.cols;
    for(int i=0; i<c; ++i){
        for(int j=0; j<d; ++j){
            cv::Vec3b color = object.at<cv::Vec3b>(i, j);
            unsigned char blue = color[0];
            unsigned char green = color[1];
            unsigned char red = color[2];
            largeBackground.at<cv::Vec3b>(i,j) = cv::Vec3b(blue, green, red);
        }
    }
}
