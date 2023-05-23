pth = pth.o # make 会隐式推导出 pth.c 依赖

# make file 的默认目标
pth: ${pth} 
	@echo 
	gcc -o pth ${pth} 
	./pth
	make clean 

.PHONY: clean
clean:
    @echo
    rm pth ${pth}