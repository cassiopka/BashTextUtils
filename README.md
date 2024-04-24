# Bash Text Utils - README.md

Этот проект предоставляет реализации на C двух основных утилит текстового редактора Bash: cat и grep. Эти утилиты часто используются для манипулирования и анализа текстовых файлов в среде терминала Linux.

## Реализованные утилиты:

### cat:

- Отображает содержимое файлов в стандартный вывод.
  
- Предлагает различные варианты управления форматом вывода, включая:
  
    - Нумерация строк: Нумерация строк с помощью -n или только непустых строк с -b.
    
    - Показ непечатаемых символов: Отображение табуляций и управляющих символов с -v или -t и -e для маркеров конца строки.
    
    - Сжатие пустых строк: Объединение последовательных пустых строк в одну с помощью -s.

### grep:

- Поиск шаблонов в файлах и отображение совпадающих строк.

- Поддерживает обширные возможности сопоставления шаблонов, включая:

    - Регулярные выражения: Использование полного синтаксиса регулярных выражений для сложного сопоставления шаблонов.
    
    - Учет регистра: Игнорирование регистра с опцией -i.
    
    - Несколько шаблонов: Сопоставление нескольких шаблонов с помощью опции -e или чтение шаблонов из файла с -f.
    
- Предоставляет возможности управления выводом:

    - Подсчет совпадений: Отображение только количества совпадений с -c.
    
    - Подавление имен файлов: Пропуск имен файлов в выводе с -h.
    
    - Список совпадающих файлов: Отображение только имен файлов, содержащих совпадения, с -l.
    
    - Номера строк: Включение номеров строк совпадающих строк с -n.
    
    - Только совпадающие: Печать только совпавших частей строк с -o.
    
    - Инвертирование совпадений: Выбор несовпадающих строк с -v.

## Структура проекта:

- `src/cat`: Содержит исходный код, заголовочные файлы и Makefile для сборки утилиты cat.

- `src/grep`: Включает исходный код, заголовочные файлы и Makefile для сборки утилиты grep.

- `src/testing`: Предоставляет тестовые файлы, файлы шаблонов и вспомогательные программы для тестирования обеих утилит.

## Сборка и тестирование:

1. Перейдите в каталог желаемой утилиты (src/cat или src/grep).
2. Запустите make для компиляции и сборки утилиты.
3. Используйте make test для выполнения предоставленного набора тестов и проверки функциональности по различным тестовым случаям.

## Использование:

Использование каждой утилиты повторяет оригинальные команды Bash:

- cat: `./my_cat [ОПЦИИ] [ФАЙЛ...]`
- grep: `./my_grep [ОПЦИИ] ШАБЛОН [ФАЙЛ...]`

Для полной информации о доступных опциях и примерах использования обратитесь к man-страницам оригинальных команд cat и grep.
