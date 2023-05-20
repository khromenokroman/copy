# Аналог copy (bash) "Сильное заявление"

## Задача сделать программу похожую на copy

ТЗ нет :)

## Инструкция по сборке

Требуется компиялтор с поддержкой C++17

Для сборки проекта необходимо выполнить следующую команду
```
cd /tmp
git clone https://github.com/khromenokroman/copy/tree/master
cd copy
mkdir build && cd build
cmake ..
cmake --build .
```

### Запуск

```
copy 1.exe 23.exe
```
