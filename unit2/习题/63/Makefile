single: test-prime.c
	gcc test-prime.c -o test-prime -lm

multi: multi-test-prime.c
	gcc multi-test-prime.c -o multi-test-prime -lm

test-single: single
	time ./test-prime

test-multi: multi
	time ./multi-test-prime

clean:
	rm ./test-prime ./multi-test-prime
