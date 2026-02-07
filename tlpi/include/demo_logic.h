#ifndef DEMO_LOGIC_H
#define DEMO_LOGIC_H

#ifdef __cplusplus
extern "C" {
#endif

// Writes 'len' bytes of 'data' to 'filename'.
// Returns the number of bytes written on success, or -1 on error.
int write_data_to_file(const char* filename, const char* data, int len);

#ifdef __cplusplus
}
#endif

#endif // DEMO_LOGIC_H