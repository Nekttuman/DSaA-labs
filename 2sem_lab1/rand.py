from random import randint

f = open("./test_data/100000.txt", 'w')

l = []
for i in range(100000):
    a = randint(-1000000,1000000)
    if a in l:
        i-=1
        continue
    l.append(a)
    f.write(str(a)+" ")
    if i%1000 == 0:
        print(i)
