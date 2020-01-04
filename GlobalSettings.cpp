#include "GlobalSettings.h"
#include <map>
#include <regex>

void global::readCmdParams(int argc, char **argv, vector< pair<string, list<float *>> > cmd_params)
{
    for (int i = 1; i < argc - 1; i++) {
        for (auto &rx_and_list : cmd_params) {
            if ( regex_match(argv[i], regex(rx_and_list.first)) )
            {
                string next_param(argv[i+1]);
                smatch match;

                for (list<float *>::iterator it = rx_and_list.second.begin(); it != rx_and_list.second.end(); ++it) {
                    regex_search(next_param, match, regex("([0-9]*[.])?[0-9]+"));
                    *(*it) = (match[0].str().empty()) ? 0.f : stof(match[0].str());
                    next_param = match.suffix().str();
                }
            }
        }
    }
}

float &global::setting(const string &key)
{
    static map<string, float> holder;
    return holder[key];
}
