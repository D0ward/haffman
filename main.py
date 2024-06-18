import subprocess
import pickle

file_name = input('Enter name file ')

#make haffman code
subprocess.call('c++ src/haffman.cpp -o haffman')
if input('Your os windows/linux ')[0].lower() == 'w':
    subprocess.call(f'./haffman.exe {file_name}')
else:
    subprocess.call(f'./haffman.out {file_name}')

#get haffman code
with open('output.txt') as file:
    n = int(file.readline())
    codes = dict()
    for _ in range(n):
        letter, code = file.readline().split()
        codes[code] = letter
    encode_text = file.readline()

#create file
new_file = input('Enter name new file ')
with open(new_file, "wb") as file:
    while len(encode_text) % 8 != 0:
        encode_text += '0'

    b = bytearray()

    for i in range(0, len(encode_text), 8):
        byte = encode_text[i:i+8]
        b.append(int(byte, 2)) 
    pickle.dump(b, file)
