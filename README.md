# msfa [![Build Status](https://travis-ci.com/maidis/msfa.svg?branch=master)](https://travis-ci.com/maidis/msfa)

msfa loosely base on Nettention's [ChangeIncludeHeaderBackslashToSlash](https://github.com/Nettention/ChangeIncludeHeaderBackslashToSlash) and [this Perl one-liner](https://stackoverflow.com/questions/573430/include-header-path-change-from-windows-to-linux):

```bash
perl -i.bak -pe 'tr!\\!/! if /^\s*#\s*include\b/' *.cpp
```

If you don't have Perl:

```bash
find .  -type f -name \* | xargs grep '#include' | grep '\\' |awk -F: '{print $1}'|sort| uniq | xargs -n1 perl -i.bak -pe 'tr!\\!/! if /^\s*#\s*include\b/'
```

This tool changes backslash symbol `\` to slash symbol `/` in your C or C++ include header file statements. For example:

```cpp
#include <SFML\Graphics.hpp>
```

will be changed to:

```cpp
#include <SFML/Graphics.hpp>
```

This tool works all C/C++ source files in the directory you specify.


# Usage

```bash
msfa <your directory> <your file extensions>
```

Example:

```bash
msfa /home/maidis/BattleCity-master/ cpp,h
```
