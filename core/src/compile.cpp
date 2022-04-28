#include "compile.h"

#include <stdlib.h>

std::vector<size_t> find_all_occurences_of(const std::string &data, std::string toSearch)
{
    std::vector<size_t> returnVec;
    size_t pos = data.find(toSearch);
    while (pos != std::string::npos)
    {
        returnVec.push_back(pos);
        pos = data.find(toSearch, pos + toSearch.size());
    }
    return returnVec;    
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::vector<std::string> get_params(const std::string &data, std::string of, const std::vector<size_t> &at)
{
    std::vector<std::string> outStrings;
    for (auto occurence: at)
    {
        size_t idx = occurence;
        char ch = data[idx];
        std::string buf;
        while (ch != '\n' && ch != '\0')
        {
            idx++;
            buf += ch;
            ch = data[idx];
        }
        // std::cout << buf << '\n';
        replace(buf, (of + "(\"").c_str(), "");
        replace(buf, "\")", "");
        replace(buf, ";", "");
        // std::cout << buf << '\n';
        outStrings.push_back(buf);
    }
    return outStrings;
}

std::string get_file_string(const char *path)
{
    std::ifstream ifs(path);
    return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}

void compile(const char *srcPath, const char *outPath)
{
    const std::string &file = get_file_string(srcPath);

    const std::vector<size_t> &add_include_dir = find_all_occurences_of(file, "add_include_dir");
    const std::vector<size_t> &add_option = find_all_occurences_of(file, "add_option");
    const std::vector<size_t> &add_link_libraries = find_all_occurences_of(file, "add_link_libraries");
    const std::vector<size_t> &add_link_library_path = find_all_occurences_of(file, "add_link_library_path");
    const std::vector<size_t> &add_src_path = find_all_occurences_of(file, "add_src_path");
    const std::vector<size_t> &add_o_file = find_all_occurences_of(file, "add_o_file");


    const std::vector<std::string> &add_include_dir_params = get_params(file, "add_include_dir", add_include_dir);
    const std::vector<std::string> &add_option_params = get_params(file, "add_option", add_option);
    const std::vector<std::string> &add_link_libraries_params = get_params(file, "add_link_libraries", add_link_libraries);
    const std::vector<std::string> &add_link_library_path_params = get_params(file, "add_link_library_path", add_link_library_path);
    const std::vector<std::string> &add_src_path_params = get_params(file, "add_src_path", add_src_path);
    const std::vector<std::string> &add_o_file_params = get_params(file, "add_o_file", add_o_file);
    
    std::string cmd = "";
    cmd += "g++" + std::string(" -shared -fPIC ");
    for (auto &option: add_option_params)
    {
        cmd += option + " ";
    }
    for (auto &include: add_include_dir_params)
    {
        cmd += "-I " + include + " ";
    }
    for (auto &src: add_src_path_params)
    {
        cmd += src + " ";
    }
    cmd += srcPath + std::string(" -o ") + outPath + " ";
    for (auto &o_file: add_o_file_params)
    {
        cmd += o_file + " ";
    }
    for (auto &linked_path: add_link_library_path_params)    
    {
        cmd += "-L " + linked_path + " ";
    }
    for (auto &linked_lib: add_link_libraries_params)
    {
        cmd += "-l" + linked_lib + " ";
    }
    std::cout << cmd << '\n';
    system(cmd.c_str());
}
