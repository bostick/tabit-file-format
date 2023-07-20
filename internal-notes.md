
# Internal notes of reverse-engineering TabIt


## Overview

Using reverse-engineering tools such as Ghidra and/or IDA Pro to analyze the TabIt executable.

Efforts to reverse-engineer TabIt are hindered by a few factors:
* compiled with Borland Delphi Pascal 2.0, released in 1996.
* Windows SEH (Structured Exception Handling), not well supported in Ghidra




## identifying information

installer used:
TabIt-2.03-full.exe


from PEiD:

Borland Delphi 2.0


Zlib 1.2.3 is embedded





## function offsets

0040a544 Format

0040a558 FmtStr

004190d8 TStream.ReadBuffer

00470124 openFile

00479e9c Zlib_zmemzero

00479eb0 Zlib_zmemcpy

00479ec4 ZAlloc

00479f00 ZFree

00479f08 checkOutOfMemory

0047a1a0 InflateX

0047a244 Inflate2 (not specific to metadata)

0047a3a8 Inflate1 (not specific to metadata)

0047a484 Zlib_adler32

0047aadc Zlib_deflateReset

0047ad10 Zlib_putShortMSB

0047ad38 Zlib_flush_pending

0047ad8c Zlib_deflate

0047b04c Zlib_deflateEnd

0047b100 Zlib_deflateCopy

0047b298 Zlib_read_buf

0047b2e4 Zlib_lm_init

0047b5a8 Zlib_fill_window

0047b6b8 Zlib_deflate_stored

0047bf0c Zlib_inflateReset

0047bfc8 Zlib_inflateInit2_

0047c090 Zlib_inflateInit

0047c0a0 Zlib_fixedtables

0047c0c0 Zlib_updatewindow

0047c1c4 Zlib_inflate

0047d0d8 Zlib_inflateSetDictionary

0047d1c0 Zlib_syncsearch

0047d208 Zlib_inflateSync

0047d2f4 Zlib_inflateCopy

0047d434 Zlib_inflate_table

0047d8a4 Zlib_tr_static_init

0047d8a8 Zlib_tr_init

0047d918 Zlib_init_block

0047dce8 Zlib_build_tree

0047e684 Zlib_build_bl_tree

0047e9e0 Zlib_tr_stored_block

0047ea9c Zlib_tr_align

0047ed68 Zlib_tr_flush_block

0047f040 Zlib_compress_block

0047f500 Zlib_set_data_type

0047f568 Zlib_bi_flush

0047f7a8 Zlib_inflate_fast

0047fcd0 crc32WithAcc

0047fd00 crc32

004b9218 somethingWithINIFiles

004b9534 somethingTabit000File

004c86f8 scanBlocksThing

004c8724 scanSingleBlock

004c8744 scan2Blocks

004c8780 scanString

004ca054 seekThingUsedDuringSave

004caba4 dumpTBT

004c9290 parseTBT












## structs

TBT_header_struct

0x00: string magic
0x03: byte versionNumber
0x04: byte tempo1
0x05: byte trackCount
0x06: Pascal255 versionString (5 bytes)
0x0b: byte bitfieldThing:
0x0c: byte[28] unused1
0x28: short barCountGE70
0x2a: short spaceCount6f
0x2c: last nonempty space up to 6f, unused >= 0x70
0x2e: short tempo2
0x30: uint metadataLen
0x34: int crc32Rest
0x38: int totalByteCount
0x3c: int crc32Header







TBT_z4096_struct (4164 = 0x1044 bytes)

0x00: TFileStream * TFileStreamObject
0x04: uint metadataLen
0x08: byte[4096] data
0x1008: z_stream
0x1040: byte
0x1041: byte
0x1042: byte
0x1043: byte






offsets in first big thing

0x364: ?
0x668: TBT_song_struct *
0x674: ?
0x6a8: ?
0x6c0: ?





offsets in TBT_song_struct

0x0c: a string?
0x30: some function called during init
0x34: some function called during init, some function called at end of parsing
0x38: spaceCount
0x3a: 
0x3c: ?, TList_Get is called on it
0x46:
0x48: ? usually set to 0
0x4c: title
0x50: artist
0x54: album
0x58: transcribedBy
0x5c: comment
0x60: track count? zeroed during init
0x64: tempo
0x68: tracks, array of 15 track pointers
0xa4: some thing that is iterated through during construction (and seems to be end of track objects)
0xa8: some thing that is iterated through during construction
0xb1: zeroed during init
0xb4: seems to be another string, file name?





offsets in track objects (size AT LEAST 98 = 0x62 bytes)

0x0: ? something with reading Registry ?
0x2: unused ?
0x4: spaces struct array pointer
0x8: allocatedThing1 pointer, indexed by spaceCount6f?
0xc: ? set in FUN_004c7654, seems to always be 0
0x10: vmPtr for space
0x14: vmPtr for allocatedThing1
0x18: ?
0x1c: stringCount
0x20: clean guitar
0x24: muted
0x28: volume
0x2c: pan
0x30: reverb
0x34: chorus
0x38: modulation
0x3c: pitchBend
0x40: midi channel
0x44: highest note?, if stringCount == 6 && drum == 1 && version < 0x6b, then set to 99
0x48: transposeHalfSteps
0x4c: midiBank (cannot change in TabIt UI? maybe disabled in later version?)
0x50: dontLetRing
0x51: topLineText
0x52: bottomLineText
0x53: displayMIDINoteNumbers
0x54: tuning (8 bytes)
0x5c: drum?
0x60: spaceCount (2 bytes) ?





offsets in space objects (size 24 = 0x18 bytes)

0x00: note
0x01: note
0x02: note
0x03: note
0x04: note
0x05: note
0x06: note
0x07: note
0x08: effect
0x09: effect
0x0a: effect
0x0b: effect
0x0c: effect
0x0d: effect
0x0e: effect
0x0f: effect
0x10: change
0x11: top text
0x12: bottom text
0x13: change value,  decimal 19
0x14:
0x15:
0x16: ?, set in FUN_004c77ac and FUN_004c776c, seems to always be 1
0x17: ?, set in FUN_004c77ac and FUN_004c776c, seems to always be 1





## fixing function calling conventions




Borland register

https://en.wikipedia.org/wiki/X86_calling_conventions#Borland_register

Evaluating arguments from left to right, it passes three arguments via EAX, EDX, ECX. Remaining arguments are pushed onto the stack, also left to right.








## Assert

this works:

```
int __usercall Assert@<eax>(char *@<eax>, char *@<edx>, int@<ecx>)
```




##

this seems correct:

void __usercall sub_4C8A38(int barCount@<eax>)



the call is:
sub_4C8A38(*(unsigned __int16 *)&HEADER[40]);



































steps for loading IDA Pro

##
keep processor type MetaPC



##
Options > Compiler...

Compiler: Delphi

Calling Convention: Pascal

NO!

Fastcall ?





##
run TabIt.idc


File > Script file...






##
load tbt-structs.h





##

load function names

Zlib functions
TabIt functions




























immediate steps for TabIt RE


## understand and fix negative stack offsets



read:

https://hex-rays.com/blog/negated-structure-offsets/




seeing stuff like:
```
*(_BYTE *)(*(_DWORD *)(*(_DWORD *)(a2 - 0x50) + 0x30) + 16 * v5 + 8) = 1;
```

































notes on Zlib


#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)





#define UPDATE(...) adler32(...)



#define Z_BINARY   0
#define Z_TEXT     1
#define Z_ASCII    Z_TEXT   /* for compatibility with 1.2.2 and earlier */
#define Z_UNKNOWN  2
/* Possible values of the data_type field (though see inflate()) */







































notes on Ghidra




Ghidra: Fix in_, extraout_, in_stack_ decompiler variables

https://www.youtube.com/watch?v=9Fo99X2YNKA







ghidra tutorials



Ghidra quickstart & tutorial: Solving a simple crackme

https://www.youtube.com/watch?v=fTGTnrgjuGA




Reverse Engineering SkiFree

https://twitter.com/Foone/status/1536053690368348160











































notes on Delphi



## what is @LStrAsg ?

https://stackoverflow.com/questions/12837129/string-const-why-different-implementation-for-local-and-result

This function is used when assigning to global variables.


LStrAsg(Dest, Source)





## LStrSetLength

"Long String SetLength"



@LStrLAsg



It turns out that string := const is implemented with different calls, depending on LValue:

    Result: AnsiString -> LStrAsg
    Result: UnicodeString: -> UStrAsg
    Local var: UnicodeString: -> UStrLAsg
    Local var: AnsiString: -> LStrLAsg









































