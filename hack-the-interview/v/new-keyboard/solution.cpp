#include <bits/stdc++.h>

/*
 * Complete the 'receivedText' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING S as parameter.
 */


std::string receivedText(std::string S) {
    
    std::string temp("");
    std::stringstream ss_buf;
    
    bool numlock_on = true;
    
    for (const auto& c : S) {
        
        if (c == '<') {
            ss_buf << temp;
            temp = ss_buf.str();
            ss_buf.str("");
        }
        else if (c == '>') {
            ss_buf << temp;
            temp = "";
        }
        else if (c == '*') {
            temp = ss_buf.str();
            temp.erase(temp.size()-1);
            ss_buf.str(temp);
            temp = "";
        }
        else if (c == '#') {
            numlock_on = !numlock_on;
        }
        else if (std::isdigit(c)) {
            if (numlock_on)
                ss_buf << c;
        }
        else {
            ss_buf << c;
        }
        
        std::cout << ss_buf.str() << std::endl;
    }
    
    if (!temp.empty()) ss_buf << temp;
    
    return ss_buf.str();
}

int main()
{
    std::ofstream fout(getenv("OUTPUT_PATH"));

    std::string S;
    std::getline(std::cin, S);

    std::string result = receivedText(S);

    fout << result << "\n";

    fout.close();

    return 0;
}

