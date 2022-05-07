
def covert_from_miles(x):
    y = x * 5280 / 4854
    k = round(y*1000)
    return (y, k)
    
    

def print_convertion(x):
    (y, k) = covert_from_miles(x)
    output = "{:.2f} English miles equals {:.2f} Roman miles or {} paces.".format(x, y, k)
    print(output)


if __name__ == '__main__':
    x = float(input())
    while x != 0:
        print_convertion(x)
        x = float(input())
        
