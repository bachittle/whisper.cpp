# Simple Whisper.cpp Example

This is a simplified version of the whisper.cpp main program, designed to provide a clean starting point for transcription projects. It demonstrates the basic usage of the whisper.cpp library with minimal code and dependencies.

## Features

Basic features included:
- WAV file input processing
- Model loading and initialization 
- Language selection
- Multi-threading support
- Plain text output

## Usage

```bash
# Basic usage
./simple input.wav

# With options
./simple -t 4 -l en -m models/ggml-base.en.bin input.wav
```

### Command Line Options

```
  -h,       --help          Show this help message and exit
  -t N,     --threads N     Number of threads to use during computation (default: 4)
  -l LANG,  --language LANG Spoken language (default: en)
  -m FNAME, --model FNAME   Model path (default: models/ggml-base.en.bin)
```

## When to Use Simple vs Main

### Use Simple When You Need

- A clean starting point for your own whisper.cpp project
- Basic audio transcription functionality
- Minimal code to understand the whisper.cpp workflow
- A foundation for building custom features

### Use Main (Full Version) When You Need

1. Advanced Audio Processing:
   - Speaker detection (diarization)
   - Audio context controls
   - Offset and duration controls
   - Speaker turn detection

2. Multiple Output Formats:
   - VTT (video subtitles)
   - SRT (subtitle format)
   - CSV (spreadsheet format)
   - JSON (structured data)
   - LRC (lyrics format)
   - WTS (karaoke format)

3. Advanced Model Controls:
   - Beam search parameters
   - Temperature settings
   - Entropy thresholds
   - Probability thresholds
   - Grammar-guided generation
   - Token suppressions

4. Additional Features:
   - Translation capabilities
   - Language auto-detection
   - GPU acceleration
   - OpenVINO support
   - Progress visualization
   - Detailed timestamps
   - Colored output
   - Initial prompts

## Code Structure

The simple example consists of three main files:
- `simple.cpp`: The main program (~150 lines)
- `CMakeLists.txt`: Build configuration
- `README.md`: This documentation

This is significantly more approachable than the full main.cpp which is over 1000 lines of code.

## Development Path

1. Start with this simple version to understand the basic workflow
2. Move to the main version when you need specific advanced features
3. Use the main version as reference for implementing custom features
