#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

void escape_in_code_blocks(std::string& s) {
    auto f = [&](const std::string& open, const std::string& close) {
        size_t p = 0;
        while ((p = s.find(open, p)) != std::string::npos) {
            size_t e = s.find(close, p + open.size());
            if (e == std::string::npos) break;
            size_t b = p + open.size();
            std::string r;
            for (char ch : s.substr(b, e - b)) {
                switch (ch) {
                    case '<': r += "&lt;"; break;
                    case '>': r += "&gt;"; break;
                    case '&': r += "&amp;"; break;
                    case '"': r += "&quot;"; break;
                    case '\'': r += "&apos;"; break;
                    default: r += ch;
                }
            }
            s.replace(b, e - b, r);
            p = b + r.size();
        }
    };
    f("<code>", "</code>");
    f("<pre class=\"code\">", "</pre>");
}
int main(int argc, char ** argv)
{
	using std::ifstream;
	using std::ofstream;
	using std::string;
	for (int i = 1; i < argc; i++)
	{
		ifstream fin;
		fin.open(argv[i]);
		char ch;
		string html_context;
		if (fin.is_open())
		{
			while(fin.get(ch))
				html_context += ch;
		}
		else
		{
			std::cerr << "Can't open" << argv[i] << std::endl;
			exit(EXIT_FAILURE);
		}
		fin.close();
		escape_in_code_blocks(html_context);
		ofstream fout;
		string output_file = string(argv[i]) + ".html";
		fout.open(output_file);
		if(fout.is_open())
		{
			for(char c: html_context)
				fout.put(c);
		}
		else
		{
			std::cerr << "Can't open" << output_file << std::endl;
			exit(EXIT_FAILURE);
		}
		fout.close();
	}
}
