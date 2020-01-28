# lambda is good when you want to use anonymous functions inside other functions

def getAdditionFunction(num):
    return lambda a: a+num

if __name__ == "__main__":
    addL = getAdditionFunction(10)
    for i in range(0, 10):
        print(addL(i))