#include <boost/program_options.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class CommandLineOptions {
public:
    CommandLineOptions(int argc, char* argv[])
        : public_options("Options")
    {
        initialize();
        parse(argc, argv);
    }

    void usage(std::ostream& os) const
    {
        os << "Usage: " << std::endl;
        os << "  xcpp [OPTIONS] <file>" << std::endl
           << std::endl;
        os << public_options << std::endl;
    }

    const std::vector<std::string>& getIncludePath() const { return path_include; }
    const std::vector<std::string>& getLibrariesPath() const { return path_libraries; }
    const std::string& getInputFile() const { return input_file; }

private:
    void initialize()
    {
        // clang-format off
        public_options.add_options()
            ("include-path,I", boost::program_options::value<std::vector<std::string>>(&path_include), "include file path")
            ("link-lib-path,L", boost::program_options::value<std::vector<std::string>>(&path_libraries), "link libraries file path")
            ;

        hidden_options.add_options()
            ("input-file", boost::program_options::value<std::string>(&input_file), "input file")
            ;
        // clang-format on

        position_options.add("input-file", 1);
    }

    void parse(int argc, char* argv[])
    {
        boost::program_options::options_description options_description;
        options_description.add(public_options).add(hidden_options);

        boost::program_options::variables_map vm;
        boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv).options(options_description).positional(position_options).run(), vm);
        boost::program_options::notify(vm);
    }

private:
    boost::program_options::options_description public_options;
    boost::program_options::options_description hidden_options;
    boost::program_options::positional_options_description position_options;

    std::vector<std::string> path_include;
    std::vector<std::string> path_libraries;
    std::string input_file;
};

class Environment {
public:
    Environment(const CommandLineOptions& options)
    {
        inititalize(options);
    }

    const std::filesystem::path& getSourceFile() const { return source_file; }

private:
    void inititalize(const CommandLineOptions& options)
    {
        using namespace std::filesystem;

        std::error_code err;
        working_path = current_path(err);

        if (exists(working_path / options.getInputFile())) {
            source_file = canonical(working_path / options.getInputFile());
        }
    }

private:
    std::filesystem::path working_path;

    std::filesystem::path source_file;
    std::list<std::filesystem::path> include_path;
};

class SourceFile {
public:
    SourceFile(const Environment& env_)
        : env(env_)
    {
    }

    const Environment& environment() const noexcept { return env; }
    const std::string& text() const noexcept { return source; }

    bool read()
    {
        std::ifstream ifs(env.getSourceFile());
        source = std::string {
            std::istreambuf_iterator<char> { ifs }, std::istreambuf_iterator<char> {}
        };

        return true;
    }

private:
    const Environment& env;
    std::string source;
};

void parse(const SourceFile& source)
{
    const char* text = source.text().c_str();
    std::size_t text_size = source.text().length();

    for (std::size_t i = 0; i < text_size; ++i) {
        std::cout.put(text[i]);
    }
}

int main(int argc, char* argv[])
{
    Environment env(CommandLineOptions(argc, argv));
    SourceFile source_file(env);

    std::cout << env.getSourceFile() << std::endl;
    if (source_file.read())
        parse(source_file);

    return 0;
}