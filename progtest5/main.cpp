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

int cmpInt(int a, int b) {
    if (a > b) {
        return 1;
    }
    else {
        return -1;
    }
}
int cmpDouble(double a, double b) {
    if (a > b) {
        return 1;
    }
    else {
        return -1;
    }
}
class CTimeStamp {
public:
    CTimeStamp(int year,
               int month,
               int day,
               int hour,
               int minute,
               double sec) :year(year), month(month), day(day), hour(hour), minute(minute), sec(sec) {};


    int Compare(const CTimeStamp &x) const {
        if ((year == x.year) && (month == x.month) && (day == x.day) && (hour == x.hour) && (minute == x.minute) && (sec == x.sec))
            return 0;

        if (year != x.year)
            return cmpInt(year, x.year);
        if (month != x.month)
            return cmpInt(month, x.month);
        if (day != x.day)
            return cmpInt(day, x.day);
        if (hour != x.hour)
            return cmpInt(hour, x.hour);
        if (minute != x.minute)
            return cmpInt(minute, x.minute);
        if (sec != x.sec)
            return cmpDouble(sec, x.sec);

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
       << setfill('0') << setw(2) << x.day << " "
       << setfill('0') << setw(2) << x.hour << ":"
       << setfill('0') << setw(2) << x.minute << ":"
       << setfill('0') << setw(2) << fixed << setprecision(3) << x.sec;

    return os;
}

class CMail {
public:
    CMail(const CTimeStamp &timeStamp,
          const string &from,
          const string &to,
          const string &subject)
            :stamp(timeStamp), from(from), to(to), subject(subject) {}



    int CompareByTime(const CTimeStamp &x) const {
        return (stamp.Compare(x));
    }

    int CompareByTime(const CMail &x) const {
        return (stamp.Compare(x.stamp));
    }

    const string &From(void) const {
        return from;
    }

    const string &To(void) const {
        return to;
    }

    const string &Subject(void) const {
        return subject;
    }

    const CTimeStamp &TimeStamp(void) const {
        return stamp;
    }
    //"2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
    friend ostream &operator<<(ostream &os,
                               const CMail &x) {
        os << x.stamp << " " << x.from << " -> " << x.to << ", subject: " << x.subject;
        std::cout << x.stamp << " " << x.from << " -> " << x.to << ", subject: " << x.subject << endl;
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
    bool cmpString(string a, string b) {
        return(a < b);
    }
    bool vecCmpTime(CTimeStamp b, shared_ptr<CMail>  a) {
        if (a->stamp.Compare(b) <= 0)
            return 0;
        else
            return 1;
    }
    class cmpTime {
    public:
        bool operator()(const CTimeStamp a, const CTimeStamp b) const {
            if (a.Compare(b) >= 0)
                return 0;
            else
                return 1;
        }
    };

    class tmpMail {
    public:
        tmpMail(CTimeStamp stamp, string domain, string message)
                :SStamp(stamp), toStamp(stamp), domain(domain), message(message), receivedFrom(false), receivedSubject(false) {}
        ~tmpMail() = default;
        CTimeStamp SStamp;
        CTimeStamp toStamp;
        string domain;
        string message;
        string from;
        string subject;
        bool receivedFrom;
        bool receivedSubject;
        bool receivedTo;
    };

    class CMailLog {
    public:
        int ParseLog(istream &in);

        list<CMail> ListMail(const CTimeStamp &from,
                             const CTimeStamp &to) const;

        set<string> ActiveUsers(const CTimeStamp &from,
                                const CTimeStamp &to) const;

    private:
        map<string, tmpMail> unfinished;
        map<CTimeStamp, vector<shared_ptr<CMail> >, cmpTime> finished;
    };

    int parseMonth(string tmp) {
        string months[11] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Nov", "Dec" };
        for (int i = 0; i <= 11; i++) {
            if (tmp == months[i]) {
                return i + 1;

            }
        }
        return 0;
    }

    int CMailLog::ParseLog(istream &in) {
        string tmp;
        int counter = 0;
        while (std::getline(in, tmp)) {// gets line of the log
            std::istringstream iss;
            iss.str(tmp);
            int year;
            int month;
            int day;
            int hour;
            int minute;
            double sec;
            char dummy1;
            char dummy2;
            string domain;
            string mailId;
            string monthPreParse;
            string message;


            // parses the line into individual strings based on space
            iss >> monthPreParse;
            month = parseMonth(monthPreParse);

            iss >> day >> year >> hour >> dummy1 >> minute >> dummy2 >> sec >> domain >> mailId;
            if (dummy1 != ':' || dummy2 != ':') {
                std::cout << "Cas spatny format";
            }

            while (!iss.eof()) { // should be end of line
                string tmp;
                iss >> tmp;
                message += tmp;
                if (!iss.eof())
                    message += ' ';
            }


            CTimeStamp tmpStamp(year, month, day, hour, minute, sec);
            tmpMail insMail(tmpStamp, domain, message);

            if (message.find("subject=") == 0) { // first we look if there is an unfinished waiting from, if not we insert, if there is we switch found subject
                message.erase(0, 8);
                auto it = unfinished.find(mailId);
                if (it != unfinished.end()) { // found a leading mail, set subject found
                    it->second.receivedSubject = true;
                    it->second.subject = message;
                }
                else {
                    insMail.receivedSubject = true;
                    insMail.subject = message;
                    unfinished.insert(pair<string, tmpMail>(mailId, insMail));
                }
            }
            else if (message.find("from=") == 0) {
                message.erase(0, 5);
                auto it = unfinished.find(mailId);
                if (it != unfinished.end()) { // found a leading mail, set subject found
                    it->second.receivedFrom = true;
                    it->second.from = message;
                }
                else {
                    insMail.receivedFrom = true;
                    insMail.from = message;
                    unfinished.insert(pair<string, tmpMail>(mailId, insMail));
                }
            }
            else if (message.find("to=") == 0) {
                message.erase(0, 3);
                auto it = unfinished.find(mailId);
                if (it != unfinished.end()) { // found one that needs to be closed and moved
                    if (it->second.receivedFrom) { // checks if got from
                        if (!it->second.receivedTo) {
                            it->second.receivedTo = true;
                            it->second.toStamp = tmpStamp;
                            shared_ptr<CMail> ptr = make_shared<CMail>(tmpStamp, it->second.from, message, it->second.subject);
                            vector<shared_ptr<CMail>> tmpVec;
                            tmpVec.emplace_back(shared_ptr<CMail>(ptr));
                            finished.insert(pair<CTimeStamp, vector<shared_ptr<CMail> > >(tmpStamp, tmpVec));
                            counter++;
                        }
                        else {
                            if (finished[it->second.toStamp].empty()){
                                shared_ptr<CMail> ptr = make_shared<CMail>(tmpStamp, it->second.from, message, it->second.subject);
                                finished[it->second.toStamp].push_back(shared_ptr<CMail>(ptr));
                                counter++;
                            }else{
                                shared_ptr<CMail> ptr = make_shared<CMail>(tmpStamp, it->second.from, message, it->second.subject);
                                auto iter = finished.find(it->second.toStamp);
                                auto insIter = upper_bound(iter->second.begin(), iter->second.end(), tmpStamp, vecCmpTime);
                                iter->second.insert(insIter, shared_ptr<CMail>(ptr));
                                counter++;
                            }
                        }
                    }
                }
                else {
                    auto finishedIt = finished.find(tmpStamp);
                    if (finishedIt != finished.end()) {
                        counter++;
                    }
                }
            }
            else {
                continue;
            }

        }
        return counter;
    }


    list<CMail> CMailLog::ListMail(const CTimeStamp &from, const CTimeStamp &to) const {
        list<CMail> retList;
        auto beginIt = finished.lower_bound(from);
        auto endIt = finished.upper_bound(to);


        if (beginIt == finished.end())
            return retList;
        for (auto i = beginIt; i != endIt; i++) {
            for (auto const & x : beginIt->second) {
                if (x->stamp.Compare(from) >= 0 && x->stamp.Compare(to) <= 0)
                    retList.push_back(*(x));
            }
            beginIt++;
        }
        return retList;
    }

    set<string> CMailLog::ActiveUsers(const CTimeStamp &from, const CTimeStamp &to) const {
        set<string> retSet;
        auto beginIt = finished.lower_bound(from);
        auto endIt = finished.upper_bound(to);
        if (beginIt == finished.end())
            return retSet;
        for (auto i = beginIt; i != endIt; i++) {
            for (auto const & x : beginIt->second) {
                if (x->stamp.Compare(from) >= 0 && x->stamp.Compare(to) <= 0) {
                    retSet.insert(x->from);
                    retSet.insert(x->to);
                }
            }
            beginIt++;
        }
        return retSet;
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
    assert(m.ParseLog(iss) == 8);
    mailList = m.ListMail(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 23, 59, 59));
    assert(printMail(mailList) ==
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
    assert(printMail(mailList) ==
           "2019-03-29 13:36:13.023 person3@fit.cvut.cz -> user76@fit.cvut.cz, subject: New progtest homework!\n"
           "2019-03-29 14:18:12.654 office13@fit.cvut.cz -> boss13@fit.cvut.cz, subject: \n"
           "2019-03-29 14:58:32.000 PR-department@fit.cvut.cz -> HR-department@fit.cvut.cz, subject: Business partner\n");
    mailList = m.ListMail(CTimeStamp(2019, 3, 30, 0, 0, 0),
                          CTimeStamp(2019, 3, 30, 23, 59, 59));
    assert(printMail(mailList) == "");
    users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 23, 59, 59));
    assert(printUsers(users) ==
           "CEO@fit.cvut.cz, CIO@fit.cvut.cz, HR-department@fit.cvut.cz, PR-department@fit.cvut.cz, archive@fit.cvut.cz, boss13@fit.cvut.cz, dean@fit.cvut.cz, office13@fit.cvut.cz, person3@fit.cvut.cz, user76@fit.cvut.cz, vice-dean@fit.cvut.cz");
    users = m.ActiveUsers(CTimeStamp(2019, 3, 28, 0, 0, 0),
                          CTimeStamp(2019, 3, 29, 13, 59, 59));
    assert(printUsers(users) == "person3@fit.cvut.cz, user76@fit.cvut.cz");
    return 0;
}

#endif /* __PROGTEST__ */
