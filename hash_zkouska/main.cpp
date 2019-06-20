#include <string>
#include <iostream>
#include <cassert>

using namespace std;

struct TItem {
    TItem(string key, string val, TItem* nextHash,TItem* nextOrd, TItem * prevOrd)
            :m_Key(key),m_Val(val),m_NextHash(nextHash),m_NextOrder(nextOrd),m_PrevOrder(prevOrd){}

    string m_Key,m_Val;
    TItem * m_NextHash, * m_NextOrder, * m_PrevOrder;
};

class CHash{
public:
    CHash (int m) : m_Table(NULL), m_Size(m), m_FirstOrder(NULL) {
        m_Table=new TItem*[m];
        for (int i =0; i<m; i++){
            m_Table[i]=NULL;
        }
    }
    ~CHash(){

    }
    bool IsSet(string key){
        TItem * tmp = m_Table[hashFn ( key )];
        while(tmp != NULL && tmp->m_Key != key)
            tmp = tmp->m_NextHash;
        if(tmp == NULL) return false;
        return true;
    }
    CHash(CHash &) = delete;
    CHash & operator = (CHash &) = delete;

    bool Ins(string key, string val){
        TItem* tmp= new TItem(key, val, NULL, NULL, NULL);
        int index = hashFn(key);
        // order
        if (m_Table[index]==NULL){ // map
            m_Table[index]=tmp;
        }else{
            TItem* ListIterator=m_Table[index];
            if(ListIterator->m_Key==tmp->m_Key){
                delete tmp;
                return false;
            }
            while(ListIterator->m_NextHash){
                if(ListIterator->m_Key==tmp->m_Key){
                    delete tmp;
                    return false;
                }
                ListIterator=ListIterator->m_NextHash;
            }
            ListIterator->m_NextHash=tmp;
        }

        if(m_FirstOrder!=NULL){ // find the last order
            TItem* iterator=m_FirstOrder;
            while(iterator->m_NextOrder){
                iterator=iterator->m_NextOrder;
            }
            tmp->m_PrevOrder=iterator;
            iterator->m_NextOrder=tmp;
            m_LastOrder=tmp;
        }else{
            m_FirstOrder=tmp;
            m_LastOrder=tmp;
        }

    }

    template <typename func>
    void ForEach(func f){
        TItem * tmp = m_FirstOrder;
        while(tmp != NULL){
            f(tmp);
            tmp =  tmp->m_NextOrder;
        }
    }

private:
    TItem **        m_Table;
    unsigned int    m_Size;
    TItem *         m_FirstOrder, * m_LastOrder;
    unsigned int hashFn(string & str){
        std::hash<std::string> hash_fn;
        return hash_fn(str)%m_Size;
    }
};

int main(int argc, char** argv) {
    CHash hashtable(100);
    assert(hashtable.Ins("h1","car"));
    assert(!hashtable.Ins("h1","auto"));
    assert(hashtable.Ins("h2","phone"));
    assert(hashtable.Ins("h3","field"));
    assert(hashtable.Ins("h4","house"));
    assert(hashtable.Ins("h5","tree"));
    hashtable.ForEach([](TItem * it ){
        cout<<it->m_Key<<" - "<<it->m_Val<<endl;
    });

    return 0;
}