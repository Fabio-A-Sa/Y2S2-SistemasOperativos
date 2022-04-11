rm -r testfile.txt
echo "first line\nsecond line" >> testfile.txt
gcc mychmode.c
ls -l testfile.txt
./a.out 755 testfile.txt
./a.out 799 testfile.txt