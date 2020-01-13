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

    checkSettings();
}

float &global::setting(const string &key)
{
    static map<string, float> holder;
    return holder[key];
}

void global::checkSettings()
{
    if (setting("screen_width") < 640.f)
        setting("screen_width") = 640.f;

    if (setting("screen_height") < 480.f)
        setting("screen_height") = 480.f;

    if (setting("map_width") < setting("screen_width"))
        setting("map_width") = setting("screen_width");

    if (setting("map_height") < setting("screen_height"))
        setting("map_height") = setting("screen_height");

    if (setting("num_asteroids") == 0.f)
        setting("num_asteroids") = 10.f;

    if (setting("num_ammo") == 0.f)
        setting("num_ammo") = 1.f;
}
