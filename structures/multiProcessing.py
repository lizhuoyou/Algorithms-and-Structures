from time import time

def mainNo1():
    start = time()
    total = 0
    numberList = [x for x in range(1, 100000001)]
    for number in numberList:
        total += number
    print(total)
    end = time()
    print("Execution time: %.3fs" % (end-start))


from multiprocessing import Process, Queue


def taskHandler(currList, resultQueue):
    total = 0
    for n in currList:
        total += n
    resultQueue.put(total)

def mainNo2():
    start = time()
    processes = []
    numList = [x for x in range(1, 100000001)]
    global resultQueue
    resultQueue = Queue()
    index = 0
    for _ in range(8):
        p = Process(target=taskHandler, args=(numList[index:index+12500000], resultQueue))
        index += 12500000
        processes.append(p)
        p.start()
    for p in processes:
        p.join()
    total = 0
    while not resultQueue.empty():
        total += resultQueue.get()
    print(total)
    end = time()
    print("Execution time: %.3fs" % (end-start))

if __name__ == "__main__":
    mainNo1()
    mainNo2()