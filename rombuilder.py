import struct


f = open("testrom", 'wb')

f.write(struct.pack(">BBBB", 0xD, 0xE, 0xA, 0xD))

f.close()
