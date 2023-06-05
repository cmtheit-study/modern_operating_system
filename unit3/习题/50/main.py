import matplotlib.pyplot as plt
import numpy as np
import magic
import os
import pathlib

def is_system_executable(file_path):
    file_type = magic.from_file(file_path)
    return 'executable' in file_type.lower()

def get_paths():
    return os.environ.get("PATH").split(':')

datas = []

for d in get_paths():
    root_dir = pathlib.Path(d)
    for file in root_dir.glob("*"):
        if file.is_file() and is_system_executable(file):
            datas.append(os.path.getsize(file))

datas.sort();
mean = np.mean(datas)
std = np.std(datas)

sigm = 0.8

# 定义上下界
lower_bound = mean - sigm * std
upper_bound = mean + sigm * std

# 过滤数据
filtered_data = [x for x in datas if lower_bound <= x <= upper_bound]
# plt.xscale('log');
plt.hist(filtered_data, bins=1000, edgecolor='black');
plt.show();