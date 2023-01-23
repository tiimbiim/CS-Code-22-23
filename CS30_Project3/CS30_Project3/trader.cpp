#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string getName(string& data) {

    //string should be in format DAY|NAME|TRADE_TYPE|NUM
    //want to grab NAME from there

    string isoNameAct;
    string name;
    string nameOnly;

    isoNameAct = data.substr(data.find_first_of("|"), data.find_last_of("|"));
    name = isoNameAct.substr(isoNameAct.find_first_not_of("|"), isoNameAct.find_last_not_of("|"));
    nameOnly = name.substr(0, name.find("|"));

    return nameOnly;

}

bool containsName(vector<string> v, string name) {

    string btName;

    for (auto& a : v) {

        btName = a.substr(a.find('|') + 1);

        if (btName == name) {

            return false;                   //if the name is found, return false so the if statement in findPotentialBadTraders fails

       }

    }

    return true;

}

vector<pair<int,string>> collectPriceDiff(vector<string> v) {

    vector<pair<int,string>> pd;
    pair<int, string> priceDiffDay;

    string identify;
    string day;

    string priceFull;
    string priceInit;
    string priceCurr;
    int priceDiff = 0;

    string stockNum;
    int sellProfit;

    size_t c;
    size_t p;

    priceFull = v.front();
    p = priceFull.find('|');
    priceInit = priceFull.substr(2, p + 1);

    for (auto& i : v) {

        identify = i;

        day = i.substr(0, i.find('|'));
        c = count(identify.begin(), identify.end(), '|');

        if (c == 3) {

            stockNum = i.substr(i.find_last_of("|") + 1);
            sellProfit = stoi(stockNum);

        }
        else if (c == 3 && day != "0") {


            stockNum = i.substr(i.find_last_of("|") + 1);
            sellProfit = stoi(stockNum) * priceDiff;


        }
        else if (c == 1) {

            priceCurr = i.substr(i.find('|') + 1);

            if (priceInit != priceCurr) {

                priceDiff = stoi(priceCurr) - stoi(priceInit);

                priceDiffDay.first = priceDiff;
                priceDiffDay.second = day;

                pd.push_back(priceDiffDay);

                priceInit = priceCurr;

            }


        }

    }

    return pd;

}

vector<string> sortVec(vector<string>& v) {

    for (int i = 0; i < v.size(); i++) {

        for (int t = 0; t < v.size(); t++) {

            if (v[i].substr(v[i].find('|')+1).compare(v[t].substr(v[t].find('|')+1)) < 0 && v[i].substr(0, v[i].find('|')) == v[t].substr(0, v[t].find('|'))) {

                std::swap(v[i], v[t]);

            }
        }
    }


    return v;
}

vector<string> findPotentialBadTraders(vector<string> v) {
    
    const int BUY_PROFIT_THRESHOLD = 500000;
    const int SELL_PROFIT_THRESHOLD = -500000;
    const int DAY_DIFF_THRESHOLD = 3;

    vector<string> bt;
    vector<int> pd;

    string identify;
    string day;
    int dayDiff;

    string stockNum;
    int netProfit;

    size_t delimCounter;


    for (auto& p : collectPriceDiff(v)) {

       /* cout << "EXAMINING THE POTENTIAL PROFITS AND LOSSES ON DAY " << p.second
            << " WITH A PRICE CHANGE OF " << p.first << endl;*/

        for (auto& i : v) {

            identify = i;
            day = i.substr(0, i.find('|'));
            delimCounter = count(identify.begin(), identify.end(), '|');
            dayDiff = stoi(p.second) - stoi(day);


            if (delimCounter == 3 && day == "0") {

                stockNum = i.substr(i.find_last_of("|") + 1);
                netProfit = stoi(stockNum) * p.first;


                if (i.find("SELL") != std::string::npos) {

                    if (netProfit <= SELL_PROFIT_THRESHOLD && dayDiff <= DAY_DIFF_THRESHOLD) {

                        if (containsName(bt, getName(i))) {

                            cout << "This has been flagged as a suspiscious trade:" << endl;

                            cout << getName(i) << " sold " << stockNum << " stocks on day " << day << endl;
                            cout << "On day " << p.second << ", the price changes by " << p.first
                                << " which prevents a loss of " << netProfit << " in " << dayDiff << " days\n" << endl;


                            bt.push_back(day + "|" + getName(i));
                        }
                    }

                }
                else {

                    if (netProfit >= BUY_PROFIT_THRESHOLD && dayDiff <= DAY_DIFF_THRESHOLD) {

                        if (containsName(bt, getName(i))) {

                            cout << "This has been flagged as a suspiscious trade:" << endl;

                            cout << getName(i) << " bought " << stockNum << " stocks on day " << day << endl;
                            cout << "On day " << p.second << ", the price changes by " << p.first
                                << " which results in a profit of " << netProfit << " in " << dayDiff << " days\n" << endl;

                            bt.push_back(day + "|" + getName(i));
                        }
                    }

                }

            }
            else if (delimCounter == 3) {


                stockNum = i.substr(i.find_last_of("|") + 1);
                netProfit = stoi(stockNum) * p.first;


                if (i.find("SELL") != std::string::npos) {

                    if (netProfit <= SELL_PROFIT_THRESHOLD && dayDiff <= DAY_DIFF_THRESHOLD) {

                        if (containsName(bt, getName(i))) {

                            //find(bt.begin(), bt.end(), susTrader) == bt.end()

                            cout << "This has been flagged as a suspiscious trade:" << endl;

                            cout << getName(i) << " sold " << stockNum << " stocks on day " << day << endl;
                            cout << "On day " << p.second << ", the price changes by " << p.first
                                << " which prevents a loss of " << netProfit << " in " << dayDiff << " days\n" << endl;


                            bt.push_back(day + "|" + getName(i));
                        }
                    }

                }
                else {

                    if (netProfit >= BUY_PROFIT_THRESHOLD && dayDiff <= DAY_DIFF_THRESHOLD) {

                        if (containsName(bt, getName(i))) {

                            cout << "This has been flagged as a suspiscious trade:" << endl;

                            cout << getName(i) << " bought " << stockNum << " stocks on day " << day << endl;
                            cout << "On day " << p.second << ", the price changes by " << p.first
                                << " which results in a profit of " << netProfit << " in " << dayDiff << " days\n" << endl;


                            bt.push_back(day + "|" + getName(i));
                        }
                    }

                }

             
            }

        }

    }

    sortVec(bt);

    return bt; 

}

int main() {

    ifstream in("C:\\Users\\timbi\\OneDrive\\Desktop\\tmbm\\school\\Elco\\CS30\\input.txt");
    string str;

    if (!in) {
        cerr << "No input file" << endl;
        exit(0);
    }

    vector<string> inputVec;
    while (getline(in, str)) {
        inputVec.push_back(str);
    }

    vector<string> resV = findPotentialBadTraders(inputVec);

    cout << "The following traders have been flagged as suspiscious: " << endl;
    cout << "------------------------------------------------------------" << endl;
    for (const string& r : resV) {
        cout << r << endl;
    }
    return 0;
}