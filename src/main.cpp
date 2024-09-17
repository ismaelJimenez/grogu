#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstring>

bool iequals(const char* str1, const char* str2) {
    if (std::strlen(str1) != std::strlen(str2)) {
        return false;
    }

    return std::equal(str1, str1 + std::strlen(str1), str2, 
                      [](char a, char b) {
                          return std::tolower(static_cast<unsigned char>(a)) == 
                                 std::tolower(static_cast<unsigned char>(b));
                      });
}

void show_help() {
  std::cout << "C++'s package manager\n\n";
  std::cout << "\033[1;32mUsage: \033[1;36mgrogu \033[0;36m[COMMAND]\033[0m" << std::endl;
}

int main(int ac, char* av[]) {
  if (ac < 2) {
    show_help();

    return 1;
  }

  if (iequals(av[1], "new")) {
    if (ac < 3) {
      std::cout << "\033[1;31merror:\033[0m the following required arguments were not provided:\n";
      std::cout << "  \033[1;36m<PATH>\033[0m\n\n";
      std::cout << "\033[1;32mUsage: \033[1;36mgrogu new \033[0;36m<PATH>\033[0m\n\n";
      std::cout << "For more information, try '\033[1;36m--help\033[0m'." << std::endl;

      return 1;
    }

    std::filesystem::path path{ av[2] };

    std::filesystem::create_directories(path);
    std::filesystem::create_directories(path / "src");

    std::ofstream ofs(path / "src" / std::string("main.cpp"));
    ofs << "#include <iostream>\n";
    ofs << "int main(int argc, char* argv[])\n";
    ofs << "{\n";
    ofs << "  std::cout << \"Hello World!\" << std::endl;\n";
    ofs << "  return 0;\n";
    ofs << "}\n";
    ofs.close();

    ofs = std::ofstream{path / std::string("Grogu.toml")};
    ofs << "[package]\n";
    ofs << "name = " << path << "\n";
    ofs << "version = \"0.1.0\"\n";
    ofs.close();
  } else if (iequals(av[1], "run")) {
    std::filesystem::path path{ av[2] };

    std::filesystem::create_directories(path / "target");
    std::filesystem::create_directories(path / "target" / "build");

    std::ofstream ofs(path / "target" / std::string("CMakeLists.txt"));
    ofs << "cmake_minimum_required(VERSION 3.10)\n";
    ofs << "project(prueba)\n";
    ofs << "add_executable(prueba ../src/main.cpp)\n";
    ofs.close();

    std::filesystem::current_path(path / "target" / "build");

    system("cmake ..");
    system("cmake --build .");
    system("./prueba");
  }

  return 0;
}