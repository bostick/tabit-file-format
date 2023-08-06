typedef unsigned char   undefined;

typedef pointer32 ImageBaseOffset32;

typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
float10
typedef long long    longlong;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned int    uint3;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef short    wchar_t;
typedef unsigned short    word;
typedef struct TBT_z4096_struct TBT_z4096_struct, *PTBT_z4096_struct;

typedef struct TFileStream TFileStream, *PTFileStream;

typedef uint u_int;



struct z_stream {
    byte * next_in;
    uint avail_in;
    ulong total_in;
    byte * next_out;
    uint avail_out;
    ulong total_out;
    char * msg;
    byte * state;
    byte * zalloc;
    byte * zfree;
    byte * opaque;
    int data_type;
    ulong adler;
    ulong reserved;
};

struct TBT_z4096_struct {
    struct byte * TFileStreamObject;
    u_int Len;
    byte data[4096];
    struct z_stream strm;
    byte ended;
    byte unused1;
    byte unused2;
    byte unused3;
};

struct TFileStream {
    struct TFileStreamVT * vt; /* Virtual Function Table */
};

