import sys
from binascii import crc32

for arg in sys.argv[1:]:
	print "{checksum} - {text}".format(text=arg, checksum=str(crc32(arg) & 0xffffffff).rjust(10))
