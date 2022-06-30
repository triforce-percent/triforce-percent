#!/usr/bin/env python3
import struct
import sys

def read_header(data):
    magic, version = struct.unpack('<4sI', data[:0x8])
    if magic != b'M64\x1a':
        raise RuntimeError('Bad movie magic')
    if version != 3:
        if version == 1 or version == 2:
            raise NotImplementedError('Movie format version 1 and 2 not implemented')
        raise RuntimeError('Movie version invalid')
    header = {'magic': magic, 'version': version}
    keys = ('movie uid', 'frame count', 'rerecord count', 'fps', 'controllers',
            'unused 0x16', 'input samples', 'start type', 'unused 0x1E',
            'controller flags', 'unused 0x24', 'rom name', 'rom crc32',
            'rom country code', 'unused 0xEA', 'video plugin', 'sound plugin',
            'input plugin', 'rsp plugin', 'author', 'description')
    values = struct.unpack('<IIIBBHIHHI160s32sIH56s64s64s64s64s222s256s', data[0x8:0x400])
    header.update(dict(zip(keys, values)))
    header['rom name'] = header['rom name'].decode('ascii').rstrip('\x00')
    header['video plugin'] = header['video plugin'].decode('ascii').rstrip('\x00')
    header['sound plugin'] = header['sound plugin'].decode('ascii').rstrip('\x00')
    header['input plugin'] = header['input plugin'].decode('ascii').rstrip('\x00')
    header['rsp plugin'] = header['rsp plugin'].decode('ascii').rstrip('\x00')
    header['rom crc32'] = hex(header['rom crc32'])
    header['author'] = header['author'].decode('utf8').rstrip('\x00')
    header['description'] = header['description'].decode('utf8').rstrip('\x00')
    return header

def read_input(data, players, header=None):
    if header == None:
        header = read_header(data)
    #print(header)
    if header['version'] == 1 or header['version'] == 2:
        start = 0x200
    elif header['version'] == 3:
        start = 0x400
    else:
        raise RuntimeError('Movie version invalid')
    if len(players) != header['controllers']:
        raise RuntimeError('Requested players ' + str(players) + ' but .m64 file is for ' 
            + str(header['controllers']) + ' controllers')
    input_struct = struct.Struct(str(4*header['controllers']) + 's')
    input_iter = input_struct.iter_unpack(data[start:])
    input_data = []
    for frame in input_iter:
        input_data.append(frame[0])
    return input_data

def main():
    try:
        file = sys.argv[1]
    except:
        print('Usage {} <movie file>')
        sys.exit()
    with open(file, 'rb') as f:
        data = f.read()
    header = read_header(data)
    for k, v in header.items():
        if 'unused' in k:
            continue
        else:
            print('{}: {}'.format(k, v))
    inputs = read_input(data, header)

if __name__ == '__main__':
    main()
