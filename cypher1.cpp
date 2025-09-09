#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <array>
using namespace std;

int main() {
    // Paste ciphertext directly into a string OR read from file
    string ciphertext =
        "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi "
        "bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx "
        "ymbinlmtmipw utn qmumbr dj w ipmhh but bj rhnvwdmbr bpr "
        "yjeryrkbi jx bpr qmbm mvvjudwko bj yt wkbrusurbmbwjk "
        "lmird jk xjubt trmui jx ibndt "
        "wb wi kjb mk rmit bmiq bj rashmwk rmvp yjeryrkb mkd wbi "
        "iwokwxwvmkvr mkd ijyr ynib urymwk nkrashmwkrd bj ower m "
        "vjyshrbr rashmkmbwjk jkr cjnhd pmer bj lr fnmhwxwrd mkd "
        "wkiswurd bj invp mk rabrkb bpmb pr vjnhd urmvp bpr ibmbr "
        "jx rkhwopbrkrd ywkd vmsmlhr jx urvjokwgwko ijnkdhrii "
        "ijnkd mkd ipmsrhrii ipmsr w dj kjb drry ytirhx bpr xwkmh "
        "mnbpjuwbt lnb yt rasruwrkvr cwbp qmbm pmi hrxb kj djnlb "
        "bpmb bpr xjhhjcwko wi bpr sujsru msshwvmbwjk mkd "
        "wkbrusurbmbwjk w jxxru yt bprjuwri wk bpr pjsr bpmb bpr "
        "riirkvr jx jqwkmcmk qmumbr cwhh urymwk wkbmvb";

    array<int, 26> counts{};
    int total = 0;

    for (char c : ciphertext) {
        if (isalpha(c)) {
            counts[toupper(c) - 'A']++;
            total++;
        }
    }

    cout << fixed << setprecision(2);
    cout << "Letter | Count | Frequency (%)\n";
    cout << "-------------------------------\n";
    for (int i = 0; i < 26; i++) {
        double freq = (counts[i] * 100.0) / total;
        cout << "   " << char('A' + i) << "   | "
             << setw(5) << counts[i] << " | "
             << setw(6) << freq << "\n";
    }

    cout << "\nTotal letters: " << total << "\n";
    return 0;
}
