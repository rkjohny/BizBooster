
#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#include <vector>
#include <mutex>
#include <sstream>
#include <string>

namespace Common {
    using namespace std;

    class StringUtility {
    private:
        StringUtility() = delete;
        StringUtility(const StringUtility&) = delete;
        StringUtility& operator=(const StringUtility&) = delete;
        ~StringUtility() = delete;

        static string cm_newLineStr;
        static string cm_tabStr;

        class Initializer {
        public:
            Initializer();
        private:
            ostringstream m_ss;
        };

        static Initializer cm_initializer;

    public:
        static string Trim(const string& str);

        static void Tokenize(vector< string >& v, const string& str, const string& token, int n = 0);

        static string GetNewLineStr();

        static string GetTabLineStr();

        static void ToLower(string& str);

        static int Compare(std::string first, std::string second, bool ignore_case = false);
    };

} /* namespace Common */

#endif /* STRINGUTILS_H_ */
