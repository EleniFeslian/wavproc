# wavproc
`wavproc` is a C program designed to **validate** WAV files by checking their structure according to the **RIFF (Resource Interchange File Format) standard**. It reads a WAV file from **standard input (stdin)** and ensures that various fields follow the correct format.

## How It Works

### ✅ Checks Key WAV Format Markers
- `"RIFF"` header  
- `"WAVE"` format identifier  
- `"fmt "` subchunk  
- `"data"` subchunk  

### ✅ Validates File Integrity
Ensures that the WAV file meets the following criteria:  
- Correct **chunk sizes**  
- Proper **WAV type format**  
- **Matching sample rate** and **byte alignment**  
- **Valid bits per sample** (must be **8** or **16**)  
- **Total file size** matches expected value  

### ✅ Processes WAV Data in Little-Endian Format
Since WAV files store multi-byte numbers in **little-endian order**, the program correctly reconstructs these values when reading them.  

## Usage
To use `wavproc`, compile it using `gcc` and run it with a WAV file as input. For example:  

```sh
gcc wavproc.c -o wavproc
./wavproc < bad_riff.wav
