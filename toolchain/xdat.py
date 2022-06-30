# Extract binary data from a file as the contents of an array.
import sys, os

def xdat(i, addr, bytes, format, o):
    i.seek(addr)
    d = i.read(bytes)
    assert len(d) == bytes
    p = 0
    while p < len(d):
        if abs(format) == 1:
            c = d[p]
            p += 1
        else:
            c = (d[p] << 24) | (d[p+1] << 16) | (d[p+2] << 8) | (d[p+3])
            p += 4
        if format > 0:
            o.write(hex(c))
        else:
            if c >= 128:
                c -= 256
            o.write(str(c))
        o.write(', ')

if __name__ == '__main__':
    assert len(sys.argv) == 6
    addr = int(sys.argv[2], 0)
    bytes = int(sys.argv[3], 0)
    format = {'s8': -1, 'u8': 1, 'u32': 4}[sys.argv[4]]
    assert bytes % abs(format) == 0
    if os.path.exists(sys.argv[5]):
        os.remove(sys.argv[5])
    with open(sys.argv[1], 'rb') as i, open(sys.argv[5], 'w') as o:
        xdat(i, addr, bytes, format, o)
