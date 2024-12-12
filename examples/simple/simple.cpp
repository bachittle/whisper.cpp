#include "common.h"
#include "whisper.h"

#include <string>
#include <thread>
#include <vector>
#include <cstdio>
#include <fstream>

// command-line parameters
struct whisper_params {
    int32_t n_threads = std::min(4, (int32_t) std::thread::hardware_concurrency());
    std::string language = "en";
    std::string model = "models/ggml-base.en.bin";
    std::string fname_inp;
};

static void whisper_print_usage(int argc, char ** argv, const whisper_params & params) {
    fprintf(stderr, "\n");
    fprintf(stderr, "usage: %s [options] file.wav\n", argv[0]);
    fprintf(stderr, "\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "  -h,       --help          show this help message and exit\n");
    fprintf(stderr, "  -t N,     --threads N     number of threads to use during computation (default: %d)\n", params.n_threads);
    fprintf(stderr, "  -l LANG,  --language LANG spoken language (default: %s)\n", params.language.c_str());
    fprintf(stderr, "  -m FNAME, --model FNAME   model path (default: %s)\n", params.model.c_str());
    fprintf(stderr, "\n");
}

static bool whisper_params_parse(int argc, char ** argv, whisper_params & params) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg[0] != '-') {
            params.fname_inp = arg;
            continue;
        }

        if (arg == "-h" || arg == "--help") {
            whisper_print_usage(argc, argv, params);
            exit(0);
        }
        else if (arg == "-t" || arg == "--threads") { params.n_threads = std::stoi(argv[++i]); }
        else if (arg == "-l" || arg == "--language") { params.language = argv[++i]; }
        else if (arg == "-m" || arg == "--model") { params.model = argv[++i]; }
        else {
            fprintf(stderr, "error: unknown argument: %s\n", arg.c_str());
            whisper_print_usage(argc, argv, params);
            exit(1);
        }
    }

    if (params.fname_inp.empty()) {
        fprintf(stderr, "error: no input file specified\n");
        whisper_print_usage(argc, argv, params);
        exit(1);
    }

    return true;
}

int main(int argc, char ** argv) {
    whisper_params params;

    if (!whisper_params_parse(argc, argv, params)) {
        return 1;
    }

    // Initialize whisper.cpp context
    struct whisper_context_params cparams = whisper_context_default_params();
    struct whisper_context * ctx = whisper_init_from_file_with_params(params.model.c_str(), cparams);

    if (ctx == nullptr) {
        fprintf(stderr, "error: failed to initialize whisper context\n");
        return 1;
    }

    // Read WAV file
    std::vector<float> pcmf32;               // mono-channel
    std::vector<std::vector<float>> pcmf32s; // stereo-channel
    if (!read_wav(params.fname_inp.c_str(), pcmf32, pcmf32s, false)) {
        fprintf(stderr, "error: failed to read WAV file '%s'\n", params.fname_inp.c_str());
        return 2;
    }

    // Run the inference
    struct whisper_full_params wparams = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    wparams.print_progress = true;
    wparams.print_special = false;
    wparams.language = params.language.c_str();
    wparams.n_threads = params.n_threads;

    if (whisper_full(ctx, wparams, pcmf32.data(), pcmf32.size()) != 0) {
        fprintf(stderr, "error: failed to process audio\n");
        return 3;
    }

    // Print results
    const int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        const char * text = whisper_full_get_segment_text(ctx, i);
        printf("%s", text);
        fflush(stdout);
    }
    printf("\n");

    whisper_free(ctx);
    return 0;
}