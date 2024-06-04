# Ресурсы
Изображения, используемые в интерфейсе программы.

Компилируются с помощью [rcc](https://doc.qt.io/qt-5/rcc.html) и [зашиваются](https://doc.qt.io/qt-5/qtcore-cmake-qt5-add-resources.html#synopsis) внутрь исполняемого файла. 

Из кода ко всем ресурсам можно обращаться как к обычным картинкам, но вначале должно стоять доветочие, например:
```cpp
QPixmap pixmap(":/icons/pause_button.svg");
```
Чтобы добавить новые ресурсы, в простейшем случае нужно закинуть их в папку resources или в любую из её подпапок. Можно также создать свою подпапку и поместить файлы в неё. Чтобы приложение видело ресурсы, все новые файлы нужно дописать в файл [**resources.qrc**](https://doc.qt.io/qt-5/resources.html) как:
``` xml
<file>Путь/Относительно/Папки_resources/Картинка.Расширение</file>
```
> Внутрь секции qresource

## Пример
Допустим наш файл **resources.qrc** исходно выглядит так:
``` xml
<!DOCTYPE RCC><RCC version="1.0">
<qresource>
    <file>icons/pause_button.svg</file>
    <file>icons/play_button.svg</file>
    <file>icons/settings_button.svg</file>
    <file>icons/stop_button.svg</file>
    <file>icons/stop_button.svg</file>
</qresource>
</RCC>
```

Для добавления картинки **"image.png"**, в новую подпапку **images** (по пути: **"Reditom_manager/resources/images/image.png"**), в файл нужно было бы дописать:
``` xml
<file>images/image.png</file>
```

Тогда наш файл будет выглядеть так:

``` xml
<!DOCTYPE RCC><RCC version="1.0">
<qresource>
    <file>icons/pause_button.svg</file>
    <file>icons/play_button.svg</file>
    <file>icons/settings_button.svg</file>
    <file>icons/stop_button.svg</file>
    <file>icons/stop_button.svg</file>

    <file>images/image.png</file>
</qresource>
</RCC>
```

И чтобы создать, например, QPixmap на основе нашей новой картинки, мы должны будем передать в него путь до картинки в виде:
``` cpp
":/images/image.png"
```

Пример:
```cpp
QPixmap pixmap(":/images/image.png");
```
