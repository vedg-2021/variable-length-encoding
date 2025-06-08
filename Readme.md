# 🗜️ Variable Length Encoding System

A custom variable-length encoding implementation for efficiently storing large integers, particularly designed for file system applications where file sizes need to be stored without fixed limitations.

## 📖 Overview

In file systems, we ideally should not put any arbitrary limit on file sizes. The only limitation should be that the file size is smaller than the disk capacity. When building a disk/file system, we need an efficient way to store file size metadata while being able to distinguish where the size information ends and the actual file content begins.

This project implements a hierarchical variable-length encoding algorithm that can compress 64-bit integers into a more compact binary representation.

## ⚙️ How It Works

The encoding algorithm uses a self-describing format that stores:
1. The original number in its minimal bit representation
2. Metadata indicating how many bits are needed to represent the original number
3. Recursive metadata for the metadata itself
4. Continuation bits to indicate sequence boundaries

This creates a variable-length encoding that is space-efficient for both small and large numbers.

## 📁 Project Structure

```
├── test.c                    # Main test driver
├── run_this.c               # Core encoding/decoding functions
├── run_this.h               # Header file with function declarations
├── bit_functions/
│   ├── bit_functions.c      # Low-level bit manipulation utilities
│   └── bit_functions.h      # Bit function headers
└── Readme.md               # This file
```

## 🔨 Building and Running

### Prerequisites
- GCC compiler
- Math library support (`-lm` flag)

### Compilation
```bash
gcc test.c bit_functions/bit_functions.c run_this.c -lm -o test.out
```

### Execution
```bash
./test.out
```

## 📚 API Reference

### Core Functions

#### `char* encodeSeq(char *in, char *out)`
Encodes a large integer into variable-length format.
- **Parameters:**
  - `in`: Pointer to the input integer (up to 64-bit)
  - `out`: Output buffer for encoded data
- **Returns:** Pointer to the encoded data

#### `long long decode(char *out)`
Decodes the variable-length format back to the original integer.
- **Parameters:**
  - `out`: Pointer to the encoded data
- **Returns:** The original decoded integer

### Bit Manipulation Functions
Located in `bit_functions/`:
- `read_bit()` - Read individual bits
- `read_num()` - Read multi-bit values
- `store_num()` - Store numbers with bit-level precision
- `read_ll_num()` - Read large numbers from bit arrays
- `store_seq()` - Store sequences with continuation flags

## 💡 Example Usage

The test program demonstrates encoding and decoding of large integers:

```c
long long b8 = 0xf1f2f3f4f5f6f7f8;  // Large 64-bit integer
char *in = &b8;
char *out = NULL;
decode(encodeSeq(in, out));  // Encode then decode
```

## 🎯 Use Cases

- **File Systems**: Storing file size metadata without artificial limitations
- **Database Systems**: Variable-length integer storage
- **Network Protocols**: Efficient integer serialization
- **Data Compression**: Space-efficient number representation

## ✨ Algorithm Benefits

1. **Space Efficient**: Small numbers use fewer bits than fixed-width encoding
2. **Scalable**: Supports very large integers (up to 64-bit)
3. **Self-Describing**: No external metadata needed to decode
4. **Boundary Detection**: Clear separation between metadata and data

## 🔧 Technical Details

The encoding uses a continuation bit system similar to Protocol Buffers' varint but with custom optimizations for file system use cases. The algorithm recursively encodes the bit-length requirements, creating a hierarchical structure that minimizes space usage while maintaining fast decode performance.

## 🤝 Contributing

This project is part of academic coursework in Data Structures. Feel free to explore the code and suggest improvements.

## 📄 License

Educational use - part of SYMCA coursework project.