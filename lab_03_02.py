'''
    Множества
'''
# создание множества
b1 = set()
print("Set b1 = ", b1)
b2 = {"bear", "fox", "squirrel", "woodpecker", "woodpecker", "wolf", "hedgehog"}
print("Set b2 = ", b2)
# создание множества из строки
b3 = set("abcdabcdefg")
print("Set b3 from string: ", set(b3))
print("\n")

# Создайте строковую переменную s со значением
# "Electricity is the set of physical phenomena associated with the presence of electric charge.
#  Lightning is one of the most dramatic effects of electricity".
# Создайте множество set1 из строки s. Осуществите вывод множества set1 на экран.

s = "Electricity is the set of physical phenomena associated with the presence of electric charge. " \
    "Lightning is one of the most dramatic effects of electricity"
print(s)
set1 = set(s)
print(set1)

# Для множества set1 осуществите проход по всем его элементам с выводом на экран гласных букв.

for element in set1:
    if element in 'aeiuo':
        print(element, end=' ')

