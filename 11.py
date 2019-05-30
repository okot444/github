# Создайте функции encodeHuffman(fileIn, fileOut) и decodeHuffman(fileIn, fileOut),
# осуществляющие кодирование и декодирование текста с использованием метода Хаффмана соответственно.
# fileIn – полное имя файла с исходным текстом, fileOut – полное имя файла, куда необходимо
# записать результат. Функции возвращают True, если ошибок не возникло, и False в ином случае.
# Осуществите проверку работы функций на произвольном тексте.

import operator


def encodeHuffman(fileIn, fileOut):

    huff_table(list_dict, d)

    string2 = ''
    for i in range(len(string)):
        string2 = string2 + d.get(string[i])

    fileOut.write(string2)

    return True


def decodeHuffman(fileIn, fileOut):

    huff_table(list_dict, d)

    new_d = {value: key for key, value in d.items()}
    string2 = ''
    s = fileIn.read()
    # пока не конец строки
    i = 0
    while i < len(s):
        i += 1
        if s[:i] in new_d:
            string2 = string2 + new_d.get(s[:i])
            s = s[i:]
            i = 0
    fileOut.write(string2)


    if len(s) == 0:
        return True
    return False


# функция создаёт частотный словарь букв
# возвращает словарь
def make_dict():
    dct = dict()  # частотный словарь букв
    for letter in string:
        if letter not in d:
            dct[letter] = 0
        dct[letter] += 1
    return dct


# функция создает список из словаря и сортирует его по убыванию
def sort_list(d):
    sort_dict = d.items()
    lword_sorted = sorted(sort_dict, key=operator.itemgetter(1), reverse=True)
    return lword_sorted


# функция кодирования по Хаффману, на основе словаря ставит соотвествующий двоичный код каждому символу
def huff_table(lword_sorted, d):
    st = ''
    for i in range(len(lword_sorted)):
        st = st + lword_sorted[i][0]
    d[st[0]] = '0'  # кодирование Хаффмана
    st = st[1:]
    for i in st:
        d[i] = '1'
    for i in st[:len(st) - 1]:  # len(st)-1 : кроме последнего
        d[i] += '0'
        for j in st[1:]:
            d[j] += '1'
        st = st[1:]


# Дополните код программы lab_03_11.py. Создайте функции
# encodeLZ(fileIn, fileOut) и decodeLZ(fileIn, fileOut),
# осуществляющие кодирование и декодирование текста с использованием
# метода Лемпеля-Зива соответственно. fileIn – полное имя файла с
# исходным текстом, fileOut – полное имя файла, куда необходимо
# записать результат. Функции возвращают True, если ошибок не возникло,
# и False в ином случае. Осуществите проверку работы функций на произвольном тексте.


# создание словаря методом Л-З
def make_dictLZ():
    d_lz[''] = '0'
    


# поиск слова в словаре
# i - индекс с которого начинается слово
def search_word(i):
    while


def encodeLZ(fileIn, fileOut):


def dencodeLZ(fileIn, fileOut):







filein = open("file_text.txt", "r")  # открыть на чтение, файл с исходным текстом
fileout = open("file_encoded.txt", "w")  # открыть на запись, файл с результатом (!)


string = filein.read()  # чтение файла, запись в строку

d = dict()
d = make_dict()  # словарь частотный
list_dict = sort_list(d)  # список с частотами букв(упорядоченный по убыванию)


if encodeHuffman(filein, fileout):
    print("encode success (true)")

#fileout.seek(0)

fileout = open("file_encoded.txt", "r")
file_decode = open("file_decoded.txt", "w")

if decodeHuffman(fileout, file_decode):
    print("decode success (true)")
else:
    print("decode fail (false)")

filein.close()
fileout.close()
file_decode.close()


d_lz = dict()
