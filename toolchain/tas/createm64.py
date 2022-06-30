import struct
import sys
import random

def create_header(nplayers, nframes):
    return struct.pack('<4sIIIIBBHIHHI160s32sIH56s64s64s64s64s222s256s',
        b'M64\x1a', 3,
        0, #'movie uid'
        nframes, #'frame count'
        1337, #'rerecord count'
        60, #'fps'
        nplayers, #'controllers'
        0, #'unused 0x16'
        nframes, #'input samples'
        2, #'start type'
        0, #'unused 0x1E'
        1, #'controller flags'
        b'\x00', #'unused 0x24'
        b'Dummy N64 ROM', #'rom name'
        0, #'rom crc32'
        69, #'rom country code'
        b'\x00', #'unused 0xEA'
        b'Nintendo/SGI RDP', #'video plugin'
        b'Nintendo/SGI RSP', #'sound plugin'
        b'Nintendo PIF', #'input plugin'
        b'Nintendo/SGI RSP', #'rsp plugin'
        b'Sauraen', #'author'
        b'lol' #'description'
        )

def wait(nplayers, nframes):
    return b'\x00\x00\x00\x00' * nplayers * nframes
    
def mash_button(nplayers, nframes, buttonmask, ctrlrmask=(True, True, True, True)):
    assert(nframes % 2 == 0)
    ret = bytearray()
    for p in range(nplayers):
        ret.extend(buttonmask if ctrlrmask[p] else b'\x00\x00\x00\x00')
    return (ret + (b'\x00\x00\x00\x00' * nplayers)) * int(nframes // 2)
