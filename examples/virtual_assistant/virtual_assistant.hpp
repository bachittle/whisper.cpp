#pragma once

#include <cstdlib>

#include <string>
#include <fstream>
#include <algorithm>

namespace va {
    void process_text(std::string text) {
        printf("processing text: %s\n", text.c_str());
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);

        std::string search_str = "ivan";
        if (text.find(search_str) != std::string::npos) {
            printf("found ivan!\n");
            {
                std::string tmp_file = "build/bin/query.txt";
                std::ofstream ofs(tmp_file);
                ofs << text << std::endl;

                // system(("python examples/virtual_assistant/llm_chat.py " + tmp_file).c_str());
                printf("!!! running llm chat\n");
                system("python examples/virtual_assistant/llm_chat.py");
                printf("!!! running tts\n");
                system("python examples/virtual_assistant/tts.py");
                printf("!!! running ffplay\n");
                system("ffplay -autoexit build/bin/response.wav");
            }
        }
    }
};