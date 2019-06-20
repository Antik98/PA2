#include <iostream>
#include <cassert>
#include <functional>

using namespace std;


class CHash {
public:
    CHash(size_t size)
            : m_Table(NULL),
              m_Size(size),
              m_FirstOrder(NULL),
              m_LastOrder(NULL)
    {

        m_Table= new TItem*[size];
        for(size_t i = 0 ; i <size; i++){
            m_Table[i]=NULL;
        }

    }

    CHash(const CHash &src):m_Table(NULL), m_Size(src.m_Size), m_FirstOrder(NULL), m_LastOrder(NULL) { // deep copy
        m_Table= new TItem*[m_Size];
        for(size_t i = 0 ; i <m_Size; i++){
            m_Table[i]=NULL;
        }
        TItem* iterator= src.m_FirstOrder;
        while(iterator){
            Ins(iterator->m_Key, iterator->m_Val);
            iterator=iterator->m_NextOrder;
        }
    }

    ~CHash(void) {
        for (size_t i = 0 ; i < m_Size; i ++){
            if (m_Table[i] && m_Table[i]->m_NextHash){
                TItem* delIterator = m_Table[i]->m_NextHash;
                while(delIterator){
                    TItem* tmp= delIterator;
                    delIterator=delIterator->m_NextHash;
                    delete tmp;
                }
            }
            delete m_Table[i];
        }
        delete[] m_Table;
    }


    CHash &operator=(const CHash &src) {
        if(this == &src){
            return *this;
        }
        for (size_t i = 0 ; i < m_Size; i ++){
            if (m_Table[i] && m_Table[i]->m_NextHash){
                TItem* delIterator = m_Table[i]->m_NextHash;
                while(delIterator){
                    TItem* tmp= delIterator;
                    delIterator=delIterator->m_NextHash;
                    delete tmp;
                }
            }
            delete m_Table[i];
        }
        delete[] m_Table;
        m_FirstOrder=NULL;
        m_LastOrder=NULL;
        m_Size=src.m_Size;

        m_Table= new TItem*[m_Size];
        for(size_t i = 0 ; i <m_Size; i++){
            m_Table[i]=NULL;
        }
        TItem* iterator= src.m_FirstOrder;
        while(iterator){
            Ins(iterator->m_Key, iterator->m_Val);
            iterator=iterator->m_NextOrder;
        }
        return *this;
    }
    template<class _T>
    void ForEach(_T& stupidFunction){
        TItem* iter=m_FirstOrder;
        while(iter){
            stupidFunction(iter->m_Val);
            iter=iter->m_NextOrder;
        }
    }
    bool Ins(const string &key,
             const string &val) {
        if(IsSet(key))
            return false;

        int index = hashFn(key, m_Size);
        if(m_Table[index]==NULL){
            m_Table[index]=new TItem(key, val);
        }else{
            TItem* old= m_Table[index];
            m_Table[index]=new TItem(key, val);
            m_Table[index]->m_NextHash=old;
        }
        if(!m_FirstOrder&& !m_LastOrder){
            m_FirstOrder=m_Table[index];
            m_LastOrder=m_Table[index];
        }else {
            m_Table[index]->m_PrevOrder = m_LastOrder;
            m_LastOrder->m_NextOrder = m_Table[index];
            m_LastOrder = m_Table[index];
        }
        return true;
    }

    bool Del(const string &key) {
        if(!IsSet(key))
            return false;
        int index=hashFn(key, m_Size);

        TItem * delIter=NULL;
        TItem ** iter = &m_Table[index]; // points at begin of list
        while(*iter){
            if((*iter)->m_Key==key){ // found it
                delIter=*iter;
                *iter=(*iter)->m_NextHash;
                break;
            }
            iter=&(*iter)->m_NextHash;
        }

        if(delIter==m_LastOrder&& delIter==m_FirstOrder){ // was the only one
            m_LastOrder=NULL;
            m_FirstOrder=NULL;
        }else if(delIter==m_FirstOrder){
            delIter->m_NextOrder->m_PrevOrder=NULL;
            m_FirstOrder=delIter->m_NextOrder;
        }else if(delIter==m_LastOrder){
            delIter->m_PrevOrder->m_NextOrder=NULL;
            m_LastOrder=delIter->m_PrevOrder;
        }

        if(delIter->m_PrevOrder){
            delIter->m_PrevOrder->m_NextOrder=delIter->m_NextOrder;
        }

        if(delIter->m_NextOrder){
            delIter->m_NextOrder->m_PrevOrder=delIter->m_PrevOrder;
        }
        delete delIter;
        return true;
    }

    bool IsSet(const string &key) const {
        int index = hashFn(key, m_Size);
        TItem * iterator = m_Table[index];
        while(iterator){
            if(iterator->m_Key==key)
                return true;
            iterator = iterator->m_NextHash;
        }
        return false;
    }

private:
    struct TItem {
        TItem(const string &key,
              const string &val)
                : m_Key(key),
                  m_Val(val),
                  m_NextHash ( NULL ),
                  m_NextOrder ( NULL ),
                  m_PrevOrder ( NULL )
        {
        }

        string m_Key;
        string m_Val;
        TItem *m_NextHash;
        TItem *m_NextOrder;
        TItem *m_PrevOrder;
    };


    TItem **m_Table;
    size_t m_Size;
    TItem *m_FirstOrder;
    TItem *m_LastOrder;

    friend int main(void);

    size_t hashFn(const string &x,
                  size_t modulus) const {
        size_t h = 5381;
        for (string::size_type c : x)
            h += (h << 5) + c;
        return h % modulus;
    }
};

void print(string &val){
    cout << val << endl;
}

int main ( void )
{
    CHash x ( 100 );

    assert ( sizeof ( CHash ) == sizeof ( CHash::TItem * ) * 3 + sizeof ( size_t ) );
    assert ( sizeof ( CHash::TItem ) == sizeof ( CHash::TItem * ) * 3 + sizeof ( string ) * 2 );
    assert ( x . Ins ( "peg", "foo" )
             && x . m_Table[1] -> m_Key == "peg"
             && x . m_Table[1] -> m_Val == "foo"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder == NULL );
    assert ( x . Ins ( "bwc", "bar" )
             && x . m_Table[45] -> m_Key == "bwc"
             && x . m_Table[45] -> m_Val == "bar"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . Ins ( "jdr", "test" )
             && x . m_Table[45] -> m_Key == "jdr"
             && x . m_Table[45] -> m_Val == "test"
             && x . m_Table[45] -> m_NextHash -> m_Key == "bwc"
             && x . m_Table[45] -> m_NextHash -> m_Val == "bar"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[45] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . Ins ( "peg", "something" ) == false );
    assert ( x . Ins ( "peg", "foo" ) == false );
    assert ( x . Ins ( "bwc", "test" ) == false );
    assert ( x . Ins ( "jdr", "mudr" ) == false );
    assert ( x . Ins ( "asa", "butterfield" )
             && x . m_Table[22] -> m_Key == "asa"
             && x . m_Table[22] -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[45] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . IsSet ( "peg" ) );
    assert ( x . IsSet ( "asa" ) );
    assert ( x . IsSet ( "bwc" ) );
    assert ( x . IsSet ( "jdr" ) );
    assert ( x . IsSet ( "whf" ) == false );
    assert ( x . IsSet ( "xns" ) == false );
    assert ( x . IsSet ( "abc" ) == false );
    assert ( x . IsSet ( "ooj" ) == false );
    x.ForEach(print);

    CHash n ( x );
    assert ( n . m_Table[1] -> m_Key == "peg"
             && n . m_Table[1] -> m_Val == "foo"
             && n . m_Table[45] -> m_Key == "jdr"
             && n . m_Table[45] -> m_Val == "test"
             && n . m_Table[45] -> m_NextHash -> m_Key == "bwc"
             && n . m_Table[45] -> m_NextHash -> m_Val == "bar"
             && n . m_Table[22] -> m_Key == "asa"
             && n . m_Table[22] -> m_Val == "butterfield"
             && n . m_FirstOrder == n . m_Table[1]
             && n . m_FirstOrder -> m_NextOrder == n . m_Table[45] -> m_NextHash
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder == n . m_Table[45]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && n . m_LastOrder == n . m_Table[22]
             && n . m_LastOrder -> m_PrevOrder == n . m_Table[45]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[45] -> m_NextHash
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[1]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( n . Del ( "jdr" )
             && n . m_Table[45] -> m_Key == "bwc"
             && n . m_Table[45] -> m_Val == "bar"
             && n . m_FirstOrder == n . m_Table[1]
             && n . m_FirstOrder -> m_NextOrder == n . m_Table[45]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && n . m_LastOrder == n . m_Table[22]
             && n . m_LastOrder -> m_PrevOrder == n . m_Table[45]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[1]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( n . IsSet ( "jdr" ) == false );
    assert ( x . m_Table[1] -> m_Key == "peg"
             && x . m_Table[1] -> m_Val == "foo"
             && x . m_Table[45] -> m_Key == "jdr"
             && x . m_Table[45] -> m_Val == "test"
             && x . m_Table[45] -> m_NextHash -> m_Key == "bwc"
             && x . m_Table[45] -> m_NextHash -> m_Val == "bar"
             && x . m_Table[22] -> m_Key == "asa"
             && x . m_Table[22] -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[45] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( n . Del ( "404" ) == false );
    assert ( n . Del ( "system32" ) == false );
    assert ( n . Del ( "root" ) == false );
    assert ( n . Ins ( "xns", "test" )
             && n . m_Table[22] -> m_Key == "xns"
             && n . m_Table[22] -> m_Val == "test"
             && n . m_Table[22] -> m_NextHash -> m_Key == "asa"
             && n . m_Table[22] -> m_NextHash -> m_Val == "butterfield"
             && n . m_FirstOrder == n . m_Table[1]
             && n . m_FirstOrder -> m_NextOrder == n . m_Table[45]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22] -> m_NextHash
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && n . m_LastOrder == n . m_Table[22]
             && n . m_LastOrder -> m_PrevOrder == n . m_Table[22] -> m_NextHash
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[45]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[1]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    x = n;
    assert ( x . m_Table[22] -> m_Key == "xns"
             && x . m_Table[22] -> m_Val == "test"
             && x . m_Table[22] -> m_NextHash -> m_Key == "asa"
             && x . m_Table[22] -> m_NextHash -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[22] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . Ins ( "whf", "FIT" )
             && x . m_Table[22] -> m_Key == "whf"
             && x . m_Table[22] -> m_Val == "FIT"
             && x . m_Table[22] -> m_NextHash -> m_Key == "xns"
             && x . m_Table[22] -> m_NextHash -> m_Val == "test"
             && x . m_Table[22] -> m_NextHash -> m_NextHash -> m_Key == "asa"
             && x . m_Table[22] -> m_NextHash -> m_NextHash -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22] -> m_NextHash -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[22] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[22] -> m_NextHash -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( n . m_Table[22] -> m_Key == "xns"
             && n . m_Table[22] -> m_Val == "test"
             && n . m_Table[22] -> m_NextHash -> m_Key == "asa"
             && n . m_Table[22] -> m_NextHash -> m_Val == "butterfield"
             && n . m_FirstOrder == n . m_Table[1]
             && n . m_FirstOrder -> m_NextOrder == n . m_Table[45]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22] -> m_NextHash
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == n . m_Table[22]
             && n . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && n . m_LastOrder == n . m_Table[22]
             && n . m_LastOrder -> m_PrevOrder == n . m_Table[22] -> m_NextHash
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[45]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == n . m_Table[1]
             && n . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . Del ( "xns" )
             && x . m_Table[22] -> m_Key == "whf"
             && x . m_Table[22] -> m_Val == "FIT"
             && x . m_Table[22] -> m_NextHash -> m_Key == "asa"
             && x . m_Table[22] -> m_NextHash -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22] -> m_NextHash
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[22] -> m_NextHash
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . Del ( "whf" )
             && x . m_Table[22] -> m_Key == "asa"
             && x . m_Table[22] -> m_Val == "butterfield"
             && x . m_FirstOrder == x . m_Table[1]
             && x . m_FirstOrder -> m_NextOrder == x . m_Table[45]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder == x . m_Table[22]
             && x . m_FirstOrder -> m_NextOrder -> m_NextOrder -> m_NextOrder == NULL
             && x . m_LastOrder == x . m_Table[22]
             && x . m_LastOrder -> m_PrevOrder == x . m_Table[45]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder == x . m_Table[1]
             && x . m_LastOrder -> m_PrevOrder -> m_PrevOrder -> m_PrevOrder == NULL );
    assert ( x . IsSet ( "asa" ) );
    assert ( x . IsSet ( "xns" ) == false );
    assert ( x . IsSet ( "whf" ) == false );
    assert ( x . Del ( "asa" )
             && x . m_Table[22] == NULL );
    assert ( x . Del ( "peg" )
             && x . m_Table[1] == NULL );
    assert ( x . Del ( "bwc" )
             && x . m_Table[45] == NULL );
    assert ( x . m_FirstOrder == NULL
             && x . m_LastOrder == NULL );
    return 0;
}