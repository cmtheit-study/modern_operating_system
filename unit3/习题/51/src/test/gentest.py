import numpy.random

# 32 位系统，生成随机访问的内存地址

sp_max = 0x7fffffff         # 栈指针初始值
sp = sp_max                 # 当前栈指针数值
sp_min = 0x70000000         # 站指针最小值（栈最大深度）
stack_change_rate = 0.1
stack_access_rate = 0.4

data_min = 0x20000000       # 数据段起始位置
data_last_access = None     # 上次访问数据段的地址
data_max = 0x2fffffff       # 数据段结束位置
data_access_rate = 0.2

heap_min = 0x30000000       # 堆段起始位置
heap_last_access = None     # 上次访问堆段的地址
heap_max = 0x6fffffff       # 堆段最大位置
heap_access_rate = 0.4

pc_min = 0x10000000         # 程序计数器最小值
pc = pc_min                 # 也是初始值
pc_max = 0x1fffffff         # 程序计数器最大值

access_memory_rate = 0.7    # 访问内存的概率
jump_rate = 0.1 # 需要跳跃
jump_near_rate = 0.9

def prob(rate):
    return numpy.random.random() < rate

def max_min(low, value, high):
    return min(max(low, value), high)

with open("address.txt", "w") as addresses:
    def access(adr):
        addresses.write(f'{adr} ')
    for i in range(10000):
        pc = int(min(pc + 4, pc_max))    # 从内存中取指
        access(pc)
        if prob(stack_change_rate):
            sp = int(max_min(sp_min, numpy.random.normal(sp, 16, 1), sp_max))
        else:
            if prob(access_memory_rate):   # 指令其余部分需要访问内存
                if prob(jump_rate): # 跳
                    if prob(jump_near_rate):    # 跳到附近区域
                        access(int(max_min(pc_min, numpy.random.normal(pc, 40, None), pc_max)))
                    else:                       # 跳到较远的区域
                        access(int(numpy.random.uniform(pc_min, pc_max)))
                else:
                    if prob(stack_access_rate): # 访问栈
                        access(int(numpy.random.uniform(sp - 40, sp)))
                    elif prob(data_access_rate / (data_access_rate + heap_access_rate)): # 访问数据
                        if data_last_access:
                            data_last_access = int(max_min(data_min, numpy.random.normal(data_last_access, 40), data_max))
                        else:
                            data_last_access = int(numpy.random.uniform(data_min, data_max))
                        access(data_last_access)
                    else:                       # 访问堆
                        if heap_last_access:
                            heap_last_access = int(max_min(heap_min, numpy.random.normal(heap_last_access, 40), heap_max))
                        else:
                            heap_last_access = int(numpy.random.uniform(heap_min, heap_max))
                        access(heap_last_access)