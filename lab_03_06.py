'''     Функции '''


def dictUpdate(a):
    a.update([("x", 5)])
    print("dict in function: ", a)
    return


def dictNoUpdate(a):
    a = a.copy()
    a.update([("y", 3)])
    print("dict in function: ", a)
    return


def returnFunc(a):
    def f1(a):
        print("returned f1(a): ", a)
    return f1

d = {"v": 7}
dictUpdate(d)
print("dict out of function: ", d)
dictNoUpdate(d)
print("dict out of function: ", d)
f = returnFunc(d)
print("f: ", f)
f(2)
print("\n")

# Создайте функцию returnMod, возвращающую функцию, которая осуществляет расчет остатка от деления
# переданного аргумента на 15 и вывод этого значения на экран. Вызовите функцию returnMod и
# осуществите запись возвращенного значения в переменную mod15. С использованием переменной mod15
# добейтесь выполнения расчета остатка от деления и вывода значения на экран. Ознакомьтесь с результатом.


def returnMod(a):
    print("{} mod 15 = ".format(a),end = "" )
    def ost(a):
        return a % 15
    print(ost(a))
    return ost(a)


mod15 = returnMod(31)



