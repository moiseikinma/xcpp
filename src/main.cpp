#include <filesystem>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

std::istream& operator>>(std::istream& is, std::filesystem::path& p)
{

    return is;
}

class CommandLineOptions {
public:
    CommandLineOptions(int argc, char* argv[])
        : options("Options")
    {
        initialize();
        parse(argc, argv);
    }

    void usage() const
    {
        std::cout << "Usage: " << std::endl;
        std::cout << "xcpp [OPTIONS] <file>" << std::endl
                  << std::endl;
        std::cout << options << std::endl;
    }

    const std::vector<std::string>& getIncludePath() const { return pathInc; }
    const std::vector<std::string>& getLibrariesPath() const { return pathLib; }

private:
    void initialize()
    {
        options.add_options()("include-path,I", boost::program_options::value<std::vector<std::string>>(&pathInc), "include file path")("link-lib-path,L", boost::program_options::value<std::vector<std::string>>(&pathInc), "link libraries file path");
    }
    void parse(int argc, char* argv[])
    {
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, options), vm);
        boost::program_options::notify(vm);
    }

private:
    boost::program_options::options_description options;

    std::vector<std::string> pathInc;
    std::vector<std::string> pathLib;
};

int main(int argc, char* argv[])
{
    CommandLineOptions command_line_options(argc, argv);
    
	for (auto && item : command_line_options.getIncludePath()) {
		std::cout << " Inc : " << item << std::endl;
	}

    return 0;
}