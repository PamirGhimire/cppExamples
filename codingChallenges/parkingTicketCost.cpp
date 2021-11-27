#include <string>
#include <iostream>

using namespace std;

int solution(string &E, string &L) {
    auto hh = [](const string& hhmm){return std::stoi(hhmm.substr(0, 2));};
    auto mm = [](const string& hhmm){return std::stoi(hhmm.substr(2));};

    const int diffHH = hh(L)-hh(E);
    const int diffMM = hh(L)==hh(E) ? mm(L)-mm(E) : 60-mm(E)+mm(L);

    if(diffHH > 0){
        return 2+3 + 4*(diffHH-1) + 4*(diffMM>0?1:0);
    }else{
        return 2+3;
    }         
}

int main()
{
    string E = "08:45";
    string L = "09:32";
    std::cout << stoi(E.substr(3)) << std::endl;
    // std::cout << solution(E, L) << std::endl;
    return 0;
}
