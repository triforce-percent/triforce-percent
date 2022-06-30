import sys

import m64

def convert(m64file, outfile):
    try:
        m = open(m64file, 'rb')
        mdata = m.read()
        m.close()
        out = open(outfile, 'w')
    except Exception as e:
        print(str(e))
        return None
    header = m64.read_header(mdata)
    nplayers = header['controllers']
    assert(nplayers >= 1 and nplayers <= 4)
    frames = m64.read_input(mdata, list(range(1,nplayers+1)), header)
    for f in frames:
        l = '|..'
        for p in range(nplayers):
            l += '|'
            x = int(f[4*p+2])
            y = int(f[4*p+3])
            x = x if x < 128 else x-256
            y = y if y < 128 else y-256
            l += '{:5d},{:5d},'.format(x, y)
            buttonskey = 'UDLRUDLRSZBAudrllr'
            buttonsvalues = [0, 0, 0, 0, #dummy digital stick
                0b0000100000000000, 0b0000010000000000, 0b0000001000000000, 0b0000000100000000, #D-pad UDLR
                0b0001000000000000, 0b0010000000000000, 0b0100000000000000, 0b1000000000000000, #SZBA
                0b0000000000001000, 0b0000000000000100, 0b0000000000000001, 0b0000000000000010, #C udrl (R/L!)
                0b0000000000100000, 0b0000000000010000] #LR
            buttons = int.from_bytes(f[4*p:4*p+2], byteorder='big')
            for bk, bv in zip(buttonskey, buttonsvalues):
                l += bk if (buttons & bv) else '.'
        l += '|\r\n'
        out.write(l)
    out.close()
    
if __name__ == '__main__':
    #try:
        convert(sys.argv[1], sys.argv[2])
    #except Exception as e:
    #    print(str(e))
    #    print('Usage: python3 m642bk2.py my_run.m64 temp_input_log_out.txt')
    #    sys.exit(1)
