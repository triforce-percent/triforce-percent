import sys

with open(sys.argv[1], 'rb') as infile:
	with open(sys.argv[2], 'wb') as outfile:
		while True:
			dword = infile.read(4)
			if not dword:
				break
			if len(dword) != 4:
				print('Warning, file not multiple of 4 bytes, appending zeros')
				while len(dword) < 4:
					dword = dword + b'\x00'
			outfile.write(bytes([dword[3], dword[2], dword[1], dword[0]]))