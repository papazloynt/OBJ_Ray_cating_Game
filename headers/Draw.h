
// Подключаем конфигурационный файл
// с текстурами
#include "ConfigFile.h"

// Подключаем структуру объектов
#include "RayCastStruct.h"

//Подключаем SFML
#include "SFML/Graphics.hpp"


#ifndef RAY_CAST_DRAW_H
#define RAY_CAST_DRAW_H

class Drawing{
    // Передаём массив объектов и в соответсвии с их
    // типом ортисовываем их с текстурами
    Drawing(std::array<RayCastStruct> objects);

    // Функция, с помощью которой накладываем
    // на объект текстуру
    void draw_texture(RayCastStruct);
};

#endif //RAY_CAST_DRAW_H
