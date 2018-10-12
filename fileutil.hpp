#ifndef FILEUTIL_HPP
#define FILEUTIL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

using ist = std::istreambuf_iterator<char>;
using ost = std::ostreambuf_iterator<char>;

// https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
// separated by , For example: cpp,inl ==> [ cpp, inl ]
std::vector<std::string> collectFileExts(const std::string &arg) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(arg);
  while (std::getline(tokenStream, token, ',')) {
    tokens.push_back(token);
  }
  return tokens;
}

// https://stackoverflow.com/questions/40633529/how-to-list-all-the-files-with-given-extension-from-directory-using-filesystem
// File search for each file extension
std::vector<std::string> collectFiles(std::string dir,
                                      std::vector<std::string> exts) {
  std::vector<std::string> tokens;

  // for(const auto& p : fs::directory_iterator(dir))
  for (const auto &p : fs::recursive_directory_iterator(dir)) {
    for (auto ext : exts) {
      if (p.path().extension() == '.' + ext) {
        tokens.push_back(p.path().u8string());
      }
    }
  }
  return tokens;
}

// Change the include statement if needed
std::string getChangedOrNotSourceLine(std::string line, bool &changed) {
  std::string includeLine = "#include";
  if (line.find(includeLine) == std::string::npos) {
    // not contain #include so it does not change
    return line;
  } else {
    std::string line2 = line;

    // TODO: regex not good enough, fails for:
    // #include <SFML\Graphics.hpp> // \test -> #include <SFML/Graphics.hpp> // /test
    line = std::regex_replace(line, std::regex(R"(\\)"), R"(/)");

    if (line != line2) {
      changed = true;
      // https://www.rosettacode.org/wiki/Globally_replace_text_in_several_files#C.2B.2B
      std::cout << line2 << " -> " << line << std::endl;
    }

    return line;
  }
}

#endif // FILEUTIL_HPP
