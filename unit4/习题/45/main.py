import os

fi = {}

for (dirn, dirs, files) in os.walk("/"):
    for file in files:
        try:
            fn = f'{dirn}/{file}'
            stat = os.stat(fn)
            if stat.st_nlink >= 2:
                fi.setdefault(stat.st_ino, [])
                fi[stat.st_ino].append(fn)
                print(fn)
        except:
            pass
print(fi)