# Тестовое задание на стажировку Импульс 2024

Стандарт C++: C++20. Запуск производился на ОС Ubuntu.

# Структура

### Сборка

Чтобы собрать программу необходимо, находясь в корневой папке проекта, вызвать процедуру сборки:
```bash
make
```

После сборки проекта будет создана папка build, в которой хранятся объектные файлы, а так же создан исполняемый файл task.

Чтобы избавиться от последствий сборки, можно вызвать процедуру очистки:
```bash
make clean
```

Что удалит папку build и исполняемый файл.
### Запуск

[![с++](https://skillicons.dev/icons?i=с++)](https://skillicons.dev)

Программа на вход принимает путь к файлу-сценарию с расширением .txt. 
Пример: 
```bash
./task scenaries/scenario.txt
```

В данном случае аргументом командной строки является 
```bash
./scenaries/scenario.txt
```

Обозначающий путь к файлу.

Вывод работы программы:

<details>
    <summary>Вывод</summary>
    
    09:00
    08:48 1 client1
    08:48 13 NotOpenYet
    09:41 1 client1
    09:48 1 client2
    09:52 3 client1
    09:52 13 ICanWaitNoLonger!
    09:54 2 client1 1
    10:25 2 client2 2
    10:58 1 client3
    10:59 2 client3 3
    11:30 1 client4
    11:35 2 client4 2
    11:35 13 PlaceIsBusy
    11:45 3 client4
    12:33 4 client1
    12:33 12 client4 1
    12:43 4 client2
    15:52 4 client4
    19:00 11 client3
    19:00
    1 70 05:58
    2 30 02:18
    3 90 08:01

</details>

### Результаты тестов

<details>
    <summary>Тестовый файл testScenario.txt</summary>

    Входные данные
    3
    10:00 22:00
    15
    09:45 1 clientA
    10:05 1 clientA
    10:15 1 clientB
    10:20 2 clientA 1
    10:25 2 clientB 2
    10:30 1 clientC
    10:35 2 clientC 3
    10:40 1 clientD
    10:45 3 clientD 
    10:50 1 clientE
    10:55 3 clientE
    11:00 1 clientF
    11:00 3 clientF
    12:00 1 clientG
    12:30 3 clientG

    Выходные данные
    10:00
    09:45 1 clientA
    09:45 13 NotOpenYet
    10:05 1 clientA
    10:15 1 clientB
    10:20 2 clientA 1
    10:25 2 clientB 2
    10:30 1 clientC
    10:35 2 clientC 3
    10:40 1 clientD
    10:45 3 clientD
    10:50 1 clientE
    10:55 3 clientE
    11:00 1 clientF
    11:00 3 clientF
    12:00 1 clientG
    12:30 3 clientG
    12:30 11 clientG
    22:00 11 clientA
    22:00 11 clientB
    22:00 11 clientC
    22:00 11 clientD
    22:00 11 clientE
    22:00 11 clientF
    22:00 11 clientG
    22:00
    1 180 11:40
    2 180 11:35
    3 180 11:25

</details>

<details>
    <summary>Тестовый файл testScenario2.txt</summary>

    Входные данные
    5
    10:00 22:00
    15
    09:45 1 clientA
    10:05 1 clientA
    10:15 1 clientB
    10:20 2 clientA 1
    10:25 2 clientB 2
    10:30 1 clientC
    10:35 2 clientC 3
    10:40 1 clientD
    10:45 3 clientD 
    10:50 1 clientE
    10:55 3 clientE
    10:55 2 clientE 4
    11:00 1 clientF
    11:00 3 clientF
    11:00 2 clientF 5
    12:00 1 clientG
    12:30 3 clientG
    15:53 4 clientF
    15:56 4 clientG

    Выходные данные
    10:00
    09:45 1 clientA
    09:45 13 NotOpenYet
    10:05 1 clientA
    10:15 1 clientB
    10:20 2 clientA 1
    10:25 2 clientB 2
    10:30 1 clientC
    10:35 2 clientC 3
    10:40 1 clientD
    10:45 3 clientD
    10:45 13 ICanWaitNoLonger!
    10:50 1 clientE
    10:55 3 clientE
    10:55 13 ICanWaitNoLonger!
    10:55 2 clientE 4
    11:00 1 clientF
    11:00 3 clientF
    11:00 13 ICanWaitNoLonger!
    11:00 2 clientF 5
    12:00 1 clientG
    12:30 3 clientG
    15:53 4 clientF
    15:53 12 clientG 5
    15:56 4 clientG
    22:00 11 clientA
    22:00 11 clientB
    22:00 11 clientC
    22:00 11 clientD
    22:00 11 clientE
    22:00
    1 180 11:40
    2 180 11:35
    3 180 11:25
    4 180 11:05
    5 90 04:56


</details>

