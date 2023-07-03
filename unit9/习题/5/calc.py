obj_num = 5000
dom_num = 100
al_rate = 0.01
two_rate = 0.1
other_rate = 0.89
print("保存全部保护矩阵需要", obj_num * dom_num, "个单位")
print("保存权能字列表需要", dom_num * (obj_num * al_rate + obj_num * two_rate * 2 / dom_num + obj_num * other_rate * 1 / dom_num), "个单位")
print("保存ACL需要", obj_num * (dom_num * al_rate + 2 * two_rate + other_rate), "个单位")