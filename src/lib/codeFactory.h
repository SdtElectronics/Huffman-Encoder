#include <string>
#include <vector>

template <typename T>
class codeFactory{
    public:
        template <typename C>
        codeFactory(const C &probs);

        std::vector<std::string> codeGen();
        std::vector<char> alphabetGen();

    private:
        std::vector<double> _probs;
        std::vector<std::string> codes;
        std::vector<char> chars;
};