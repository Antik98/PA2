# Viktor slaví narozeniny
Viktor slaví narozeniny a na oslavu si pozval kamarády.  Organizovat oslavy není 
nic jednoduchého, tak ses nabídl, že mu s pár věcma pomůžeš. Protože je to oslava 
moderní, používej co nejvíc STL. 

Nemusíš ošetřovat vstupy, použij přiložený testovací main a makefile. Úlohy jsou menší, po 0.5b. Jednotlivé úlohy jsou krátké, v referenčním řešení jsou na cca 3-15 řádek, včetně výpisu řešení a řádků, kde jsou jen závorky. 

Kompletní seznam konteinerů:
https://en.cppreference.com/w/cpp/container

## 1) Spočítej kamarády
Viktor se snaží zjistit, kolik je vlastně na oslavě jeho kamarádů. Říká ti, koho tu 
vidí, ale protože se hosté nesutále hýbou, je možné, že ti některé kamarády řekne 
vícekrát. Kolik je na oslavě hostů?

TIP: set

## 2) Dlouhá jména
Překopíruj jména hostů ze setu do nového seznamu (vector), pokud je délka jejich jména 
delší než zadaná mez. Použij copy_if a lambda funkci. 

## 3) Počítání bodů
Kamarádi hrají hry, při kterých postupně získávají body. Kdo získal nejvíce bodů?

TIP: map

## 4) Přepsání jmen
Při psaní jmen hostů jsi omylem měl zapnutý CapsLock. Pomocí funkce transform 
a funktoru přepiš jména hostů tak, aby první písmenko bylo velké a ostatní malá.

Příklad užití funktorů:
https://www.geeksforgeeks.org/functors-in-cpp/

## 5) Zapisování výsledků
Při zapisování výsledků závodů je potřeba ukládat jméno soutěžícího (string), jeho 
čas (double) a kategorii ve které soutěžil (char). Jak tyto údaje ukládat, pokud 
nesmíme použít vlastní třídy/struktury ani pair? 

## 6) Nejlepší úsměv
Při soutěži o nejlepší úsměv každý porotce vybere jednoho účastníka (řekne jeho číslo).
 Do dalšího kola postupují ti, pro které hlasovali alespoň dva porotci. V zadaném 
 seznamu čísel najdi všechny duplicity v lineárním čase (ne v čase n log n, použij 
 vhodný kontejner).

## 7) Úsporné dělení
Ke konci party je na čase ukázat své nejokouzlující triky z C++. Získej z funkce jediným 
voláním hodnoty podílu a zbytku po dělení dvou čísel. 
Nepoužívej vstupně-výstupní parametry, upravuj kód jen tam, kde to je dovoleno 
(/*TODO*/). (Kusy kódu jsou zakomentovány, aby se soubor v současném stavu zkompiloval).
