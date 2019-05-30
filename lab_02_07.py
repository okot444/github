# Создайте программу lab_02_07.py, которая преобразует введенное с клавиатуры двенадцатеричное число
# в систему с основанием 14 и выводит результат преобразования на экран.

p = input("введите 12ричное число:")
p1 = int(p, 12)
print(p1)
j = 0
s = ""
if p1 < 0:
    p1 = abs(p1)
    s += "-"
while p1 > 14:
    ost = p1 % 14
    print("ost = ", ost)
    if ost > 9:
        if ost == 10:
            ost = 'A'
        if ost == 11:
            ost = 'B'
        if ost == 12:
            ost = 'C'
        if ost == 13:
            ost = 'D'
    s = str(ost) + s
    p1 //= 14
if p1 > 9:
    if p1 == 10:
        p1 = 'A'
    if p1 == 11:
        p1 = 'B'
    if p1 == 12:
        p1 = 'C'
    if p1 == 13:
        p1 = 'D'
s = str(p1) + s
print(s)
s = s[::-1]

print("chislo :", s)
