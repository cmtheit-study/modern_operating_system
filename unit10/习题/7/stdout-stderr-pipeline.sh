touch rdonly.txt
chmod 0 rdonly.txt
cat rdonly.txt | echo > /dev/null
cat rdonly.txt | echo 2> /dev/null
rm -f rdonly.txt