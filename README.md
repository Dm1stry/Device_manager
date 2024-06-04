# Reditom_manager

## Обзор

* Приложение для управления установками ядерного магнитного резонанса, разработанными КФМС ИФ КФУ
* Версия 0.1
* https://github.com/asalexandrov/Reditom_manager.git

## Зависимости
- Windows
- vcpkg
- cmake
- Qt 5.15 (устанавливается через vcpkg)
- nlohmann::json (устанавливается через vcpkg)
- exprtk (устанавливается через vcpkg)

## Клонирование и сборка проекта
### Клонирование
1. В папке, где вы будете работать с проектом необходимо создать подпапку, назовем её по имени проекта и перейти в неё:
``` bash
mkdir Reditom
cd Reditom
```
2. Затем в эту папку необходимо склонировать проект:
``` bash
git clone git@github.com:asalexandrov/Reditom_manager.git
```
### Установка зависимостей
1. Установить [vcpkg](https://github.com/microsoft/vcpkg) в систему (не в папку с проектом)
2. [Добавить vcpkg в PATH](https://remontka.pro/add-to-path-variable-windows/)
3. С помощью vcpkg нужно установить qt 5.15:
``` bash
vcpkg install qt5:x64-windows
```
> Установка может занять продолжительное время, вплоть до нескольких часов, поскольку vcpkg будет собирать фреймворк из исходиков
4. Также через vcpkg нужно установить оставшиеся зависимости:
```cmd
vcpkg install nlohmann-json:x64-windows
vcpkg install exprtk:x64-windows
```
5. После установки необходимо интегрировать установленные пакеты с MVSC, для этого выполните:
``` bash
vcpkg integrate install
```
Команда выведет несколько строк, в том числе строку вида:

CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=D:/Development/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake"

Скопируйте путь, содержащийся в этой строке, он понадобится при настройке сборки проекта
### Сборка проекта
Если вы клонируете и собираете проект впервые
1. В созданной нами папке, вне проекта, которую мы назвали "Reditom" необходимо создать файл с именем "CMakeList.txt"
2. В него нужно записать следующий текст:
```cmake
cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Reditom)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

set(VCPKG_TARGET_TRIPLET x64-windows)
set(CMAKE_TOOLCHAIN_FILE Путь/До/Установленного/VCPKG/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
include(${CMAKE_TOOLCHAIN_FILE})

add_subdirectory(Reditom_manager)
```
3. В строке:
``` cmake
set(CMAKE_TOOLCHAIN_FILE Путь/До/Установленного/VCPKG/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
```
Нужно заменить "Путь/До/Установленного/VCPKG/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" на путь до файла vcpkg.cmake, который вы получили на последнем шаге установки зависимостей. В случае примера это будет выглядеть как:
```cmake
set(CMAKE_TOOLCHAIN_FILE D:/Development/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)
```

> Шаги 1-3 нужно проделать единожды, при первом клонировании репозитория, в последующие разы достаточно просто подтянуть обновления командой **vcpkg pull**, выполненной из папки Reditom_manager

4. После этого можно создать папку, где мы будем собирать наш проект и перейти в неё:
``` bash
mkdir build
cd build
```
5. И наконей собрать проект:
``` bash
cmake ..
cmake --build .
```

Или, если нужно собрать Release версию
``` bash
cmake ..
cmake --build . --config Release
```
## Документация
Вся существующая документация расположена в папке docs репозитория

## Контакты

* [Artem.S.Alexandrov](https://github.com/asalexandrov)
* [VAlikV](https://github.com/VAlikV)
* [Dm1stry](https://github.com/Dm1stry)
* [Samatgator](https://github.com/Samatgator)
* KFMS KFU
