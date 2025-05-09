# File Stat Utility


## Installation
Утилита `stat` — это инструмент командной строки, который отображает информацию о файле или каталоге, включая его тип, размер, номер инода, а также время изменения, создания и доступа.
Чтобы использовать утилиту `stat`, вам понадобится makefile:

```
make
```

Это создаст исполняемый файл с именем `stat.out`, который можно запустить из командной строки.

## Usage

Чтобы использовать утилиту `stat`, просто запустите исполняемый файл `stat.out`, а затем имя файла или каталога, о котором вы хотите получить информацию. Например:

```
./stat file.txt
```

Это выведет следующую информацию о файле `file.txt`:

```
File: file.txt
Type: regular file
Size in byte: 1234
Inode: 12345
The time the file was last modified: Fri Apr 14 12:34:56 2023
File creation time: Fri Apr 14 12:34:56 2023
Last access time of the file: Fri Apr 14 12:34:56 2023
```

Если вы хотите получить информацию о нескольких файлах, вы можете перечислить их все в качестве аргументов:

```
./stat file1.txt file2.txt 
```

Это выведет информацию для каждого файла отдельно.

