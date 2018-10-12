/*
https://stackoverflow.com/questions/573430/include-header-path-change-from-windows-to-linux
perl -i.bak -pe 'tr!\\!/! if /^\s*#\s*include\b/' *.cpp
*/

#include "fileutil.hpp"

// https://github.com/Nettention/ChangeIncludeHeaderBackslashToSlash
int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << R"(Changes #include "..\aa.h" to #include "../aa.h".)"
              << std::endl
              << R"(Args example: msfa work/MySourceFolder cpp,h,inl)"
              << std::endl;
  } else {
    try {

      std::vector<std::string> fileExts = collectFileExts(argv[2]);
      // Find all cpp, h file in the specified folder.
      std::vector<std::string> sourceFiles = collectFiles(argv[1], fileExts);

      std::vector<std::string> changedFiles;
      std::vector<std::string> unchangedFiles;
      std::vector<std::string> erroredFiles;

      std::string includeLine = "#include";

      for (auto sourceFile : sourceFiles) {
        // if an individual file fail just go to the next file
        try {

          std::ifstream infile{sourceFile};
          std::stringstream sourceLines({ist{infile}, ist{}});

          bool changed = false;

          std::string line;

          // std::cout << sourceLines.str() << endl;

          std::stringstream newSourceLines;

          while (std::getline(sourceLines, line)) {
            // std::istringstream iss(line);

            line = getChangedOrNotSourceLine(line, changed);

            newSourceLines << line << std::endl;
            // std::cout << line << endl;
          }
          infile.close();

          if (changed) {
            std::ofstream outfile;
            outfile.open(sourceFile);

            // std::cout << newSourceLines.str() << endl;
            // outfile << newSourceLines.rdbuf();
            outfile << newSourceLines.str();
            outfile.close();

            changedFiles.push_back(sourceFile);
          } else {
            unchangedFiles.push_back(sourceFile);
          }
        } catch (const std::exception &e) {

          std::cout << " a standard exception was caught, with message '"
                    << e.what() << "'\n";
          erroredFiles.push_back(sourceFile);
        }
      }

      std::cout << unchangedFiles.size() << " files are skipped. "
                << changedFiles.size() << " files are updated. "
                << erroredFiles.size() << " files are in error.\n";

    } catch (const std::exception &e) {
      std::cout << " a standard exception was caught, with message '"
                << e.what() << "'\n";
    }
  }

  return 0;
}
