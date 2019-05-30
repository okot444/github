
# Создайте словарь textDict для содержимого файла text1.txt, который приведен далее,
# по следующему принципу: ключи словаря – слова текста, значения словаря – частота появления
# слова в отрывке. Запишите словарь textDict в файл с именем textDict.txt.

file = open("text1.txt", "r")

text_dict = dict()
for line in file:
    for word in line.split():
        cl_word = word.strip('.,!-').lower()
        if cl_word not in text_dict:
            text_dict[cl_word] = 0
        text_dict[cl_word] += 1
print(text_dict)
file.close()
file = open("textDict.txt", "w")

file.write(str(text_dict.items()))
file.close()
