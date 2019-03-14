Obecné zadání 

Úlohy kompilujte a spouštějte pomocí triviálního Makefile. Použijte standard C++14, režim pedantic a výpis všech varování. Spouštějte s valgrindem (také pomocí Makefile).
Vždy ošetřujte vstupy a používejte C++, nicméně použití STL povoleno není. Všechny metody a funkce opatřete dokumentačními komentáři. Použijte objektový (nikoliv procedurální) přístup. Dlouhé metody rozdělte. Každá třída má svůj hlavičkový a zdrojový soubor (pokud uvedete vhodný důvod, je možné, aby některé třídy sdílely jeden soubor).
Nesplnění jakékoli položky vede k hodnocení 0vb. 

Do implementace můžete vložit další pomocné metody či třídy.


[2.0vb] Herní pole
Vytvořte třídu, která bude reprezentovat herní pole pro hru lodě. - Třída musí obsahovat dynamicky alokovanou 2D mřížku. Velikost mřížky (kladné dimenze) se předává jako parametry konstruktoru a dále se nemění.
- Každá pozice mřížky obsahuje informaci o tom, zda-li na pozici je voda, loď, nebo potopená loď. Využijte enum.
- Dále je potřeba herní pole vypisovat, vytvořte metodu pro tuto funkcionalitu.
- Implementujte také destruktor.
Funkčnost stačí demonstrovat na volání metod ve funkci main, není nutné nic načítat ze vstupu. 

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

[1.0vb] Herní pole II.
Do třídy přidejte následující metody:
- Přidání lodě do hrací plochy (není možné přidat loď, pokud už soupeř jednou vystřelil). Pro jednoduchost uvažujte lodě o velikostech buď x*1 nebo 1*x (vertikální či horizontální “had”). Lodě mohou sousedit, ale nesmí se překrývat.
- Dotazovací metoda, která pro zadané souřadnice vrátí informaci o tom, v jakém stavu je dané políčko.
- Metoda, která zjistí, je-li v hracím poli aktivní nějaká loď (nebo její část).
- Funkcionalitu opět demonstrujte voláním metod ve funkci main.
- Směry os si zvolte.

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

[1.0vb] Inicializace hry
Vytvořte třídu, která bude řídit jednu hru. Třída musí obsahovat dvě hrací pole. 
- Třída jedno pole náhodně naplní daným počtem lodních políček.
- Druhé pole vyplňuje uživatel přes standardní vstup (formát zvolte). Třída nesmí dovolit uživateli přidat více než určený počet lodních políček.
- Rozměry herních polí zadává uživatel přes standardní vstup na začátku hry, stejně tak počet lodních políček (logicky nemůže být počet lodí vyšší než je počet políček).
- Pro generování pseudonáhodných čísel použijte std::mt19937 (https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

[1.0vb] Samotné hraní
- Po naplnění herních polí začíná uživatel střílet na lodě protihráče (počítače), program vypíše, jestli se trefil a loď potopil, netrefil, nebo jestli se trefil, ale loď už byla potopená v jednom z předchozích tahů.
- V dalším tahu střílí na lodě hráče počítač, a to zcela náhodně.
- V každém tahu počítače se vypíše aktuální stav herního pole hráče.
- Na konci hry třída vypíše vítěze a obě herní pole.
- Pro generování pseudonáhodných čísel použijte std::mt19937 (https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine)

-------------------------------------------------
-------------------------------------------------
-------------------------------------------------
-------------------------------------------------

[1.0vb] AI
Do hotové hry implementujte cokoliv, co bude hrát proti hráči sofistikovaněji než náhodné střílení (počítač ale nesmí podvádět).