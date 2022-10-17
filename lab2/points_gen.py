import random


def generate_points(amount):
    points = []
    points_num = amount
    for i in range(points_num):
        x = random.randint(-50, 50)
        y = random.randint(-50, 50)
        if [x,y] in points:
            i-=1
            continue
        points.append([x, y])
    return points


f = open("input.txt", 'w')

ps = generate_points(100)

f.write(str(ps[0][0]) + " " + str(ps[0][1]))
for p in ps[1:]:
    f.write('\n'+str(p[0]) + " " + str(p[1]))

f.close()