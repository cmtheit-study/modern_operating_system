gcc test.c -o test
./test < input.txt > output.txt 2> error.txt abc '*' *
./test * | ./test * &
rm ./test