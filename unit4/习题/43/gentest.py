import random
import string

with open("test.txt", "w") as test:
    for i in range(0, random.randint(2 << 10, 2 << 20)):
        test.write(f'{random.choice(string.printable)}')