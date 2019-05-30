'''     Словари '''
d1 = {"day": 18, "month": 6, "year": 1983}
d2 = dict(bananas=3, apples=5, oranges=2, bag="basket")
d3 = dict([("street", "Kronverksky pr."), ("house", 49)])
d4 = dict.fromkeys(["1", "2"], 3)
print("Dict d1 = ", d1)
print("Dict d2 by dict()= ", d2)
print("Dict d3 by dict([])= ", d3)
print("Dict d4 by fromkeys = ", d4)
print("\n")

# Создайте словарь startDict с ключами ready, set, go и значениями 3, 2 и 1 соответственно тремя разными способами,
# добавляя индекс к имени переменной. Выведите получившиеся словари на экран

startDict = dict(read=3, set=2, go=1)
startDict1 = {"read": 3, "set": 2, "go": 1}
startDict2 = dict([("read", 3), ("set", 2), ("go", 1)])

print("Dict startDict = ", startDict)
print("Dict startDict1 by dict()= ", startDict1)
print("Dict startDict2 by dict([])= ", startDict2)

# Создайте словарь dict1 с ключами key1 и key2, заполнив их одинаковым значением, введенным с клавиатуры.
# Осуществите вывод словаря dict1 на экран.

dict1 = dict.fromkeys(["key1", "key2"], input("введите значение ключей"))
print(dict1)
