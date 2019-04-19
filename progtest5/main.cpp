#ifndef __PROGTEST__

#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;
int cmpInt(int a, int b){
    return (a>b)-(a<b);
}
int cmpDouble(double a, double b){
    return (a>b)-(a<b);
}
class CTimeStamp {
public:
    CTimeStamp(int year,
               int month,
               int day,
               int hour,
               int minute,
               double sec) :year(year),month(month),day(day),hour(hour),minute(minute),sec(sec){};


    int Compare(const CTimeStamp &x) const{
        if((year == x.year) && (month == x.month) && (day == x.day) && (hour == x.hour) && (minute == x.minute) && (sec == x.sec))
            return 0;

        if(cmpInt(year,x.year))
            return cmpInt(year,x.year);
        if(cmpInt(month,x.month))
            return cmpInt(month,x.month);
        if(cmpInt(day,x.day))
            return cmpInt(day,x.day);
        if(cmpInt(hour,x.hour))
            return cmpInt(hour,x.hour);
        if(cmpInt(minute,x.minute))
            return cmpInt(minute,x.minute);
        if(cmpDouble(sec,x.sec))
            return cmpDouble(sec,x.sec);


        return 0;

    };

    friend ostream &operator<<(ostream &os,
                               const CTimeStamp &x);

    int year;
    int month;
    int day;
    int hour;
    int minute;
    double sec;
};

ostream &operator<<(ostream &os, const CTimeStamp &x) {
    os << setfill('0') << setw(4) << x.year << "-"
    << setfill('0') << setw(2) << x.month << "-"
    << x.day << " "
    << x.hour << ":"
    << x.minute << ":"
    << setprecision(3)<< x.sec;

    return os;
}

class CMail {
public:
    CMail(const CTimeStamp &timeStamp,
          const string &from,
          const string &to,
          const string &subject)
          :stamp(timeStamp), from(from),to(to), subject(subject) {}


    int CompareByTime(const CTimeStamp &x) const{
        return (stamp.Compare(x));
    }

    int CompareByTime(const CMail &x) const{
        return (stamp.Compare(x.stamp));
    }

    const string &From(void) const{
        return from;
    }

    const string &To(void) const{
        return to;
    }

    const string &Subject(void) const{
        return subject;
    }

    const CTimeStamp &TimeStamp(void) const{
        return stamp;
    }

    friend ostream &operator<<(ostream &os,
                               const CMail &x){
        os << x.stamp << x.from << x.to << x.subject;
        return os;
    }

    CTimeStamp stamp;
    string from;
    string to;
    string subject;
};
// your code will be compiled in a separate namespace
namespace MysteriousNamespace {
#endif /* __PROGTEST__ */

//----------------------------------------------------------------------------------------
    class CMailLog {
    public:
        int ParseLog(istream &in);

        list<CMail> ListMail(const CTimeStamp &from,
                             const CTimeStamp &to) const;

        set<string> ActiveUsers(const CTimeStamp &from,
                                const CTimeStamp &to) const;

    private:
        map<>;
        multiset;
    };
    int parseMonth(string tmp){
        switch(tmp){
            case ("Jan"):
                return 1;
            case ("Feb"):
                return 2;
            case ("Mar"):
                return 3;
            case ("Apr"):
                return 4;
            case ("May"):
                return 5;
            case ("Jun"):
                return 6;
            case ("Jul"):
                return 7;
            case ("Aug"):
                return 8;
            case ("Sep"):
                return 9;
            case ("Oct"):
                return 10;
            case ("Nov"):
                return 11;
            case ("Dec"):
                return 12;
            default:
                return 0;
        }
    }

    int CMailLog::ParseLog(istream &in) {
        string tmp;
        while(std::getline(in,tmp)){// gets line of the log
            std::istringstream iss;
            iss.str(tmp);
            int year;
            int day;
            int hour;
            int minute;
            int sec;
            char dummy1;
            char dummy2;
            string mailId;
            string monthPreParse;
            while(!iss.eof()){           // parses the line into individual strings based on space
                iss >>  monthPreParse;
                month = parseMonth(monthPreParse);

                iss>> day >> year >> hour >> dummy1 >> minute >> dummy2 >> sec >> mailId;

                if(word.empty()){
                    cout<< "Chyba nactena mezera, prazdny string" << endl;
                }
                inputV.push_back(word);
                word.clear();
            }
            if(inputV.size()<7){ // checks if has enough words else ignores
                inputV.clear();
                continue;
            }
            int year;
            string month;
            int hour;
            int min;
            double sec;
            char inputTime[inputV[3].size()] = inputV[3];
            sscanf(inputTime, " %d:%d:%lf", &hour, &min, &sec);
            CTimeStamp tmpStamp(,,hour, min, sec);





        }
    }


    list<CMail> CMailLog::ListMail(const CTimeStamp &from, const CTimeStamp &to) const {

    }

    set<string> CMailLog::ActiveUsers(const CTimeStamp &from, const CTimeStamp &to) const {

    }

//----------------------------------------------------------------------------------------
#ifndef __PROGTEST__
} // namespace
string printMail(const list<CMail> &all) {
    ostringstream oss;
    for (const auto &mail : all)
        oss << mail << endl;
    return oss.str();
}

string printUsers(const set<string> &all) {
    ostringstream oss;
    bool first = true;
    for (const auto &name : all) {
        if (!first)
            oss << ", ";
        else
            first = false;
        oss << name;
    }
    return oss.str();
}

int main(void) {
    MysteriousNamespace::CMailLog m;
    list<CMail> mailList;
    set<string> users;
    istringstream iss;

    iss.clear();
    iss.str(
            "Mar 29 2019 12:35:32.233 relay.fit.cvut.cz ADFger72343D: from=user1@fit.cvut.cz\n"
            "Mar 29 2019 12:37:16.234 relay.fit.cvut.cz JlMSRW4232Df: from=person3@fit.cvut.cz\n"
            "Mar 29 2019 12:55:13.023 relay.fit.cvut.cz JlMSRW4232Df: subject=New progtest homework!\n"
            "Mar 29 2019 13:38:45.043 relay.fit.cvut.cz Kbced342sdgA: from=office13@fit.cvut.cz\n"
            "Mar 29 2019 13:36:13.023 relay.fit.cvut.cz JlMSRW4232Df: to=user76@fit.cvut.cz\n"
            "Mar 29 2019 13:55:31.456 relay.fit.cvut.cz KhdfEjkl247D: from=PR-department@fit.cvut.cz\n"
            "Mar 29 2019 14:18:12.654 relay.fit.cvut.cz Kbced342sdgA: to=boss13@fit.cvut.cz\n"
            "Mar 29 2019 14:48:32.563 relay.fit.cvut.cz KhdfEjkl247D: subject=Business partner\n"
            "Mar 29 2019 14:58:32.000 relay.fit.cvut.cz KhdfEjkl247D: to=HR-department@fit.cvut.cz\n"
            "Mar 29 2019 14:25:23.233 relay.fit.cvut.cz ADFger72343D: mail undeliverable\n"
            "Mar 29 2019 15:02:34.231 relay.fit.cvut.cz KhdfEjkl247D: to=CIO@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=CEO@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=dean@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=vice-dean@fit.cvut.cz\n"
            "Mar 29 2019 15:02:34.230 relay.fit.cvut.cz KhdfEjkl247D: to=archive@fit.cvut.cz\n");
    assert (m.ParseLog(iss) == 8);
    mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 23, 59, 59));
    assert (printMail(mailList) ==
            "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
            "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
            "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n"
            "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> CEO@fit.cvut.cz, subject: Business partner\n"
            "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> dean@fit.cvut.cz, subject: Business partner\n"
            "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> vice-dean@fit.cvut.cz, subject: Business partner\n"
            "2019-03-29 15:02:34.230 PR-department@fit.cvut.cz -> archive@fit.cvut.cz, subject: Business partner\n"
            "2019-03-29 15:02:34.231 PR-department@fit.cvut.cz -> CIO@fit.cvut.cz, subject: Business partner\n");
    mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 14, 58, 32));
    assert (printMail(mailList) ==
            "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
            "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
            "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n");
    mailList = m.ListMail(CTimeStamp(2019, 3, 30, 0, 0, 0),
                          CTimeStamp(2019, 3, 30, 23, 59, 59));
    assert (printMail(mailList) == "");
    users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 23, 59, 59));
    assert (printUsers(users) ==
            "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz");
    users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 13, 59, 59));
    assert (printUsers(users) == "person3@fit.cvut.cz, user76@fit.cvut.cz");
    return 0;
}

#endif /* __PROGTEST__ */
