rm -r testfile.txt
echo "first line" >> testfile.txt
echo "second line" >> testfile.txt
gcc mychmode.c
ls -l testfile.txt
./a.out 755 testfile.txt
ls -l testfile.txt
./a.out 799 testfile.txt