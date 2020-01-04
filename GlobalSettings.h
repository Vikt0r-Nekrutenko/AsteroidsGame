#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <list>
#include <vector>
#include <string>

using namespace std;

namespace global {
    void readCmdParams(int argc, char **argv, vector< pair<string, list<float *>> > cmd_params);
    float &setting(const string &key);
}

#endif // GLOBAL_SETTINGS_H
