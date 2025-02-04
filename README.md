# wavproc
This C program is designed to validate a WAV file by checking its structure according to the RIFF (Resource Interchange File Format) standard. It reads a WAV file from the standard input (stdin) and ensures that various fields follow the correct format.

Key Features & How It Works

-Reads and checks for key WAV format markers
    "RIFF" header
    "WAVE" format identifier
    "fmt " subchunk
    "data" subchunk

-Validates file integrity by ensuring:
    Proper chunk sizes
    Correct WAV type format
    Matching sample rate and byte alignment
    Valid bits per sample values (8 or 16 bits)
    Ensuring the total file size matches the expected size

-Reads & processes file in little-endian format
    Since WAV files store multi-byte numbers in little-endian order, the program reconstructs these values accordingly.
