f = open("input.txt")

snails_x = []
snails_y = []

for i in f.read().split('\n'):
    print(i)
    x,y = (int(j) for j in i.split(' '))
    snails_x.append(x)
    snails_y.append(y)



from matplotlib import pyplot as plt
plt.style.use('ggplot')
plt.plot(snails_x, snails_y, 'ro')
plt.minorticks_on()
plt.grid(which='minor', color='white',linestyle =':')
plt.show()