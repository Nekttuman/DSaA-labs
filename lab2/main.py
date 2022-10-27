from cProfile import label


def get_distance(a,b ):
    return ((a[0] - b[0])**2 + (a[1] - b[1])**2)**0.5


def get_min_distance(points, l, r):
    if r <= l:                        
        return [0, 0, 65535]

    if r - l == 1:                        
        return [l, r, get_distance(points[l], points[r])]

    if r - l == 2:                         
        d1 = get_distance(points[l], points[l+1])
        d2 = get_distance(points[l+1], points[r])
        d3 = get_distance(points[l], points[r])
        if d1 <= d2 and d1 <= d3:
            return [l, l+1, d1]
        elif d2 <= d1 and d2 <= d3:
            return [l+1, r, d2]
        else:
            return [l, r, d3]
# r-l >= 3 , get d

    m = l + (r - l) // 2
    result1 = get_min_distance(points, l, m)
    result2 = get_min_distance(points, m+1, r)
    d = min(result1[2], result2[2])
    
    # found points
    i = m
    while i <=l:                                # right direction
        if points[m][0] - points[i][0] < d:
            i -= 1
        else:
            break

    j = m
    while j<=r:                                 # left direction
        if points[j][0] - points[m][0] < d:
            j += 1
        else:
            break

    if i < m:
        i += 1

    result3 = [0, 0, inf]
    for a in range(i, m+1):          
        for b in range(m+1, j):                 
            d0 = get_distance(points[a], points[b])
            if d0 < result3[2]:
                result3 = [a, b, d0]

    return sorted([result1, result2, result3], key=lambda o: o[2])[0]




# cheking with n^2 algo


def another_way(points):
    num = len(points)
    best = [0,0, 65535]

    for i in points:
        for j in points:
            d = get_distance(i, j)
            if i != j and d < best[2]:
                best = [i,j, d]

    return best



if __name__ == "__main__":

    f = open("input.txt")

    snails_x = []
    snails_y = []

    from cmath import inf
    import numpy as np
    snails = []


    for i in f.read().split('\n'):
        x,y = (int(j) for j in i.split(' '))
        snails_x.append(x)
        snails_y.append(y)
        snails.append([x,y])


    from matplotlib import pyplot as plt
    plt.style.use('ggplot')
    plt.scatter(snails_x, snails_y, s=10)
    plt.minorticks_on()
    plt.grid(which='minor', color='white',linestyle =':')
    plt.show()


    # sort coords by x
    snails = sorted(snails, key=lambda o: o[0])

    import time

    t = time.time()
    (a,b,d) = get_min_distance(snails, 0, len(snails)-1)
    print(time.time()-t)
    print("alg divide and rule: ",snails[a], snails[b], d)
    


    plt.scatter(snails_x, snails_y, s=10)
    plt.scatter([snails[a][0], snails[b][0]], [snails[a][1], snails[b][1]], c='g')
    plt.show()

    # t = time.time()
    # (a,b,d) = another_way(snails)
    # print(time.time()-t)
    # print("n**2 alg ",a,b, d)


    # plt.scatter(snails_x, snails_y, s=10)
    # plt.scatter([a[0], b[0]], [a[1], b[1]], c='g')
    # plt.show()
