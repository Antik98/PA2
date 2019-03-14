# Zadání
George a Charlotte rádi hrají karetní hru Magic. Pravidla ještě neumí, ale ví, že balíčky karet mohou různě smíchávat, rozdělovat a otáčet. Rádi se ptají, třeba „Když z balíčku B vezmu prvních 5 karet, spojím je s balíčkem A a otočím 6. kartu, co tam bude?“. Odpověď chtějí znát co nejdřív a tobě už z neustáleho míchání karet a počítání jde hlava kolem. Rychlejší bude si na to napsat program.

Každý balíček karet má svůj název a obsahuje karty. Každá karta má název, potřebnou manu pro zahrání karty a útočnou sílu. Stáhni si kostru programu včetně očekávaného chování.

Maximální počet karet v balíčku je pro jednoduchost omezen. Nemusíš ošetřovat validitu
 vstupů, pokud to není explicitně napsáno.

 Nezapomeň si nechat zkontrolovat kód během cvičení a následně ho poslat na email s informací, do kterého bodu máš hotovo (např. 2F).
 
## 1) Základní vytvoření a výpis balíčku
a) Přetiž operátor `+=`, který přidá k balíčku kartu.

b) Napiš friend funkci přetěžující `operátor «`, který vypíše informace o balíčku. Tento
operátor je vhodné přetížit jak u třídy pro balíček, tak u třídy pro kartu. Použij ostream
 (4. přednáška slide 28).

c) Přetiž operátor `[]`, který vrátí kartu na zadané pozici.

## 2) Spojení balíčků a výjimky
d) Napiš metodu přetěžující operátor `+`, který spojí dva balíčky. Názvy balíčků spoj 
dohromady.

e) Pokud bys měl při spojování dvou balíčů překročit maximální počet karet v balíčku,
 vyhoď (libovolnou) `výjimku`. Při odchycení výjimky v mainu ji vypiš.
 
f) Pokud se bude chtít pomocí operátoru [] přistupovat ke kartě, která neexistuje 
(position<0 || positoin>=cards_count), vyhoď výjimku `std::out_of_range`. Vyhozená 
výjimka by měla 
obsahovat
 informaci (textovou) k jakému indexu jsme chtěli přistoupit a kolik bylo karet v 
 balíčku. Při odchycení výjimky v mainu ji vypiš.
 
 ## 3) Řazení a odebírání
g) Napiš metodu, která `seřadí` karty v balíčku, řadí se primárně podle nejvyššího 
attacku, 
sekundárně podle nejnižší many. Použij volání std::sort se dvěma parametrama, případně 
si dodefinuj další potřebné operátory.

h) Napiš metodu přetěžující operátor `|`, která simuluje odebrání prvních N karet z 
balíčku. Tato
 metoda vrací odebrané karty jako nový balíček. 

i) Přetěž operátor `[]` tak, aby šel zavolat jak na konstantní objekty, tak abychom ho 
mohli použít jako l-hodnotu.
```cpp
...
deck[5] = card_deamon;
...
const Deck const_deck = deck;
cout<<const_deck[4];
```  
## 4) Na zamyšlenou 
Jak doplnit následující hlavičku for cyklu **2**, aby se choval stejně jako for 
cyklus **1**?

Tělo cyklu se nesmí změnit. Je zakázáno "podtéct" proměnnou i do vysokých hodnot. 
```c++
 /*1*/
string s="ahoj";
for( int i = s.length()-1; i>=0; i-- ){
    cout << s[i]<<endl;
}
 
 /*2*/
for( unsigned int i = ?; ?; ? ){
    cout << s[i]<<endl;
}

```

## 5) Na dlouhé zimní večery
Zkus si napsat makefile, kde použiješ proměnné a zástupné symboly (`$@`, `$<`, `$^`).








