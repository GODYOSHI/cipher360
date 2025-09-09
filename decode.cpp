#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <cctype>
using namespace std;

inline int idx(char c) { return c - 'a'; }

// Apply cipher->plain mapping
string apply_mapping(const string& text, const array<int,26>& mapTo) {
    string out = text;
    for (char &c : out) {
        if (c < 'a' || c > 'z') continue; // skip spaces, punctuation
        int ci = idx(c);
        int pi = mapTo[ci];               // -1 = unknown
        if (pi != -1) {
            c = char('a' + pi);           // only replace if we know the mapping
        }
        // else: keep original ciphertext letter
    }
    return out;
}

// Show mapping table
void print_key(const array<int,26>& mapTo) {
    cout << "cipher: ";
    for (int i=0;i<26;i++) cout << char('a'+i) << ' ';
    cout << "\nplain : ";
    for (int i=0;i<26;i++) cout << (mapTo[i]==-1 ? '_' : char('a'+mapTo[i])) << ' ';
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ciphertext
    const string ciphertext =
        "lrvmnir bpr sumvbwvr jx bpr lmiwv yjeryrkbi jx qmbm wi\n"
        "bpr xjvni mkd ymibrut jx irhx wi bpr riirkvr jx\n"
        "ymbinlmtmipw utn qmumbr dj w ipmhh but bj rhnvwdmbr bpr\n"
        "yjeryrkbi jx bpr qmbm mvvjudwko bj yt wkbrusurbmbwjk\n"
        "lmird jk xjubt trmui jx ibndt\n"
        "wb wi kjb mk rmit bmiq bj rashmwk rmvp yjeryrkb mkd wbi\n"
        "iwokwxwvmkvr mkd ijyr ynib urymwk nkrashmwkrd bj ower m\n"
        "vjyshrbr rashmkmbwjk jkr cjnhd pmer bj lr fnmhwxwrd mkd\n"
        "wkiswurd bj invp mk rabrkb bpmb pr vjnhd urmvp bpr ibmbr\n"
        "jx rkhwopbrkrd ywkd vmsmlhr jx urvjokwgwko ijnkdhrii\n"
        "ijnkd mkd ipmsrhrii ipmsr w dj kjb drry ytirhx bpr xwkmh\n"
        "mnbpjuwbt lnb yt rasruwrkvr cwbp qmbm pmi hrxb kj djnlb\n"
        "bpmb bpr xjhhjcwko wi bpr sujsru msshwvmbwjk mkd\n"
        "wkbrusurbmbwjk w jxxru yt bprjuwri wk bpr pjsr bpmb bpr\n"
        "riirkvr jx jqwkmcmk qmumbr cwhh urymwk wkbmvb";

    array<int,26> mapTo;
    mapTo.fill(-1);

    cout << "Commands:\n"
         << "  set <c> <p>            (e.g., set b t)\n"
         << "  set2 <c1><c2> <p1><p2> (e.g., set2 pr he)\n"
         << "  clear <c>              (undo a mapping)\n"  // NEW COMMAND DOCUMENTED HERE
         << "  print                  (decoded text)\n"
         << "  key                    (mapping table)\n"
         << "  quit\n\n";

    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        stringstream ss(line);
        string op; ss >> op;
        if (op.empty()) continue;

        if (op == "quit" || op == "exit") break;
        else if (op == "print") {
            cout << "\n===== decoded =====\n"
                 << apply_mapping(ciphertext, mapTo) << "\n";
            cout << "==================\n";
            print_key(mapTo);
        }
        else if (op == "key") {
            print_key(mapTo);
        }
        else if (op == "set") {
            char ciph, plain; ss >> ciph >> plain;
            if (ciph<'a'||ciph>'z'||plain<'a'||plain>'z') {
                cout << "Usage: set <cipher> <plain>\n"; continue;
            }
            mapTo[idx(ciph)] = idx(plain);
            cout << "mapped " << ciph << " -> " << plain << "\n";
        }
        else if (op == "set2") {
            string cs, ps; ss >> cs >> ps;
            if (cs.size()!=2 || ps.size()!=2) {
                cout << "Usage: set2 <c1><c2> <p1><p2>\n"; continue;
            }
            mapTo[idx(cs[0])] = idx(ps[0]);
            mapTo[idx(cs[1])] = idx(ps[1]);
            cout << "mapped " << cs[0] << " -> " << ps[0]
                 << ", " << cs[1] << " -> " << ps[1] << "\n";
        }
        else if (op == "clear") { // NEW COMMAND HANDLING
            char ciph; ss >> ciph;
            if (ciph<'a'||ciph>'z') {
                cout << "Usage: clear <cipher>\n"; continue;
            }
            mapTo[idx(ciph)] = -1;
            cout << "cleared mapping for " << ciph << "\n";
        }
        else {
            cout << "Unknown command. Try: set / set2 / clear / print / key / quit\n";
        }
    }
}
