before = open("test.txt").read()
after = open("tset.txt").read()[::-1]
if before == after:
    print("test ok")
else:
    print("not pass")
    for (i, (b, a)) in enumerate(zip(before, after)):
        if b != a:
            print(f'at {i}')
            print(f'\x1b[032m{before[max(0, i - 5):min(len(before), i + 5)]}\x1b[0m\n\x1b[033m{after[max(0, i - 5):min(len(before), i + 5)]}\x1b[033m')
            break
