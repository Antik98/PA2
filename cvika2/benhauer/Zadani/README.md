# Zadání

Následující C++ kód [`src/main.cpp`](src/main.cpp) implementuje funkce pro práci se strukturou `Date` a jednoduchý program pro načtení, vypsání, seřazení a opětovné vypsání datumů ([pravopis](http://prirucka.ujc.cas.cz/?slovo=datum)). Proveďte níže uvedené úpravy. Po každé jednotlivé úpravě zkuste zkompilovat zdrojový kód a otestovat aplikaci. Pokud se ztratíte můžete využít stručnou [teorii](teorie.md) nebo kontaktujte vašeho cvičícího.

## Úpravy

Proveďte následující úpravy v zdrojovém kódu

1. Doplňte funkci `dateCompare` pro porovnání dvou struktur typu `Date`. Všimněte si klíčových slov `const` u parametrů, funkce `sort` je vyžaduje. *Při kompilaci využijte variantu s přepínačem **-DSHOW_SORTED**.*
2. Z funkce `datePrint` vytvořte metodu `Date::print`. Nezapomeňte vhodně upravit funkci `main`.
3. Metoda `Date::print` je jednoduchá a krátká, inlinujte ji.
4. Vytvořte strukturu `Person`, která bude reprezentovat osobu. U osoby chceme evidovat křestní jméno `givenName`, příjmení `familyName`, datum narození `birthDate` a pohlaví `gender`. Zvolte vhodné datové typy (můžete využít třídu [`std::string`](https://en.cppreference.com/w/cpp/string/basic_string), pro `gender` vytvořte výčtový typ). Demonstrujte vhodně ve funkci `main`.
5. Implementujte metodu pro získání (nikoli výpis) celého jména osoby `Person::getFullName` a `Person::setFullName` pro nastavení atributů `givenName` a `familyName` podle předaného parametru (poslední slovo oddělené mezerou bude `familyName`, využijte metody objektu `std::string`).
6. Implementujte metodu pro výpis všech informací o osobě `Person::print`. Demonstrujte vhodně ve funkci `main`.
7. Implementujte funkci `personCompare` pro porovnání dvou objektů typu `Person`. Nejprve podle příjmení, pak podle jména a nakonec podle data narození. *Při kompilaci využijte variantu s přepínačem **-DSHOW_SORTED**.*
8. Implementujte funkce `dateCompare` a `personCompare` jako statické metody `Date::compare` a `Person::compare`. (Později si ukážeme jak správně a intuitivně implementovat porovnávání bez použití statických metod).
9. Implementujte metody `Date::scan` a `Person::scan` pro načtení dat ze standardního vstupu. *(Vstup nemusí nutně odpovídat výstupu.)*
10. Doplňte vhodné dokumentační komentáře.
11. Upravte funkci `main` tak, aby demonstrovala použití všech vlastností. Vytvořte ve složce [`data/`](data/) testovací data pro ověření funkčnosti, alespoň 3 různé sady pro testování různých aspektů (např. nesprávný vstup, mezní hodnoty, správné zpracování). Název souborů by měl být ve tvaru [`0000_in.txt`](data/0000_in.txt) a [`0000_out.txt`](data/0000_out.txt).

## Bonusový úkol

1. Implementujte metody `Person::write` a `Person::read` pro binární zápis do souboru a čtení ze souboru.

## Příkazy pro kompilaci
```
g++ -Wall -pedantic -Wextra -g -std=c++11 src/main.cpp
g++ -Wall -pedantic -Wextra -g -std=c++11 -DSHOW_SORTED src/main.cpp
```

V rámci předmětu BI-PA2 budeme využívat verzi standardu C++11. Pokud chcete používat pokročilejší vlastnosti v domácích úkolech, nejprve si ověřte jejich funkčnost v kompilátoru systému [Progtest](https://progtest.fit.cvut.cz/).

## Vyzkoušejte si doma

- (*pokud se nestihlo vše na cvičení*) dodělat zbývající body
- Vyzkoušejte si *bonusový úkol*.
