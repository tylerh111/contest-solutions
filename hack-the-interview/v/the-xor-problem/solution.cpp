#include <bits/stdc++.h>
#include <sstream>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'maxXorValue' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING x
 *  2. INTEGER k
 */

string maxXorValue(string x, int k) {
    
    std::stringstream ss;
    
    for (auto it = x.begin(); it != x.end(); ++it) {
        if (k == 0 || *it == '1') {
            ss << '0';
        }
        else {
            ss << '1';
            k--;
        }
    }
    
    return ss.str();
}



int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string k_temp;
        getline(cin, k_temp);

        int k = stoi(ltrim(rtrim(k_temp)));

        string y = maxXorValue(s, k);

        fout << y << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

