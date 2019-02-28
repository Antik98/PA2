# Objekty

Pokud některé proměnné spolu úzce souvisí, umisťujeme je do struktury. To nám umožňuje vytvářet funkce, které pracují pouze s jedním parametrem.

```c
struct Complex
{
	double real,
	       imaginary;
};

void complexSet ( Complex & complex, double real = 0, double imaginary = 0 )
{
	complex . real = real;
	complex . imaginary = imaginary;
}

void complexPrint ( const Complex & complex )
{
	cout << complex.real << " + " << complex.imaginary << "i";
}

int main ()
{
	Complex c = { 1.0, 2.0 };
	complexPrint( c );
	complexSet( c, 2.0, 3.0 );
	complexPrint( c );
	return 0;
}
```

V C++ jsou struktury rozšířené o možnost přidání funkce. Takovou strukturu poté nazýváme **třídou** a její funkce **metodami**. Jednotlivé (instance) proměnné daného typu jsou **objekty**. Metody nepotřebují v parametru samotný objekt, mají k němu přímý přístup. V případě, že dojde ke kolizi názvů parametrů s proměnnými struktury, můžeme přistupovat k proměnným v rámci struktury pomocí prefixu `Complex::` nebo proměnné `this`, která odpovídá datovému typu `Complex *` (ukazatel na objekt). Z vnějšku přistupujeme k metodám stejně jako k proměnným.

```cpp
struct Complex
{
	double real,
	       imaginary;

	void set ( double real, double imaginary );

	void print () const;
};

void Complex::set ( double real = 0, double imaginary = 0 )
{
	this -> real = real;
	this -> imaginary = imaginary;
}

void Complex::print () const
{
	cout << real << " + " << imaginary << "i";
}

int main ()
{
	Complex c = { 1.0, 2.0 };
	c . print();
	c . set( 2.0, 3.0 );
	c . print();
	return 0;
}
```

> Všimněte si klíčového slova `const` u parametru funkce `complexPrint`. To reprezentuje, že předávaný parametr nebudeme ve funkci měnit. Jelikož metoda nepotřebuje jako parametr samotný objekt, tak se toto klíčové slovo zapisuje za **"konec hlavičky metody"**. Význam zůstává stejný, použití této metody nijak neupraví objekt samotný.

Metody deklarujeme přímo v zápisu struktury. Její definici pak uvádíme podobně jako klasickou funkci, nesmíme zapomenout na prefix `Complex::print`, který určuje k jaké třídě metoda patří. V případě jednoduchých definicí můžeme metodu inlinovat, to uděláme umístěním definice metody přímo do deklarace struktury.

```cpp
struct Complex
{
...
	void print () const
	{ cout << real << " + " << imaginary << "i"; }
...
};
```

## Klíčové slovo `const`

Klíčové slovo `const` bývá často nepochopeno začínajícími programátory. Proč bych měl vůbec chtít, aby bylo něco tzv. konstantní. Základní myšlenkou je *ochrana* programátora přes sebou nebo jinými programátory.

U parametrů jej uvádíme pokud parametr předáváme ukazatelem (*pointer*) nebo referencí, abychom nemuseli kopírovat celý objekt (strukturu). Takový objekt sice nemůžeme modifikovat, ale naše funkce (metoda) přijímá i konstantní objekty, kam patří i dočasné objekty.

Jelikož metody pracují s třídou, ke kterému patří, je tedy nutné specifikovat zda objekt, se kterým pracují je konstantní nebo není. V takovém případě za definici parametrů metody uvádíme klíčové slovo `const`. To nám znemožňuje upravovat atributy objektu, na druhou stranu můžeme takovou metodu volat i nad konstantními objekty.

```cpp
class Complex
{
...
public:
	void print () const;
};

void Complex::print () const
{
	...
}
```

## Statické metody

Typické metody pracují s objektem samotným (`this`), pokud ovšem metoda nepracuje s objektem, ale pouze se váže k třídě. Můžeme metodu implementovat jako `static` metodu. Takové metody nepracují s konkrétním objektem a jeho atributy, samotný objekt mohou přijímat v parametru. Statické metody přiřazujeme k třídě, protože s nimi mají logicky něco společného.

```cpp
class Complex
{
	...

	static bool compare ( const Complex & c1, const Complex & c2 );
};

bool Complex::compare ( const Complex & c1, const Complex & c2 )
{
	if ( c1 . real != c2 . real )
		return c1 . real < c2 . real;
	return c1 . imaginary < c2 . imaginary;
}

int main ()
{
	Complex c1( 2.0, 1.0 ), c2( 2.0, 3.0 );
	cout << Complex::compare( c1, c2 ) << endl;
	return 0;
}
```

## Dokumentační komentáře

Na přiloženém zdrojovém kódu si můžete všimnout, že od minulého cvičení zde přibyly tzv. dokumentační komentáře. Dokumentační komentář od klasického komentáře poznáte tak, že začíná `/**`, `/*!` nebo také `///`. Vždy záleží na používaném nástroji, nejčastější bývá implementována první možnost `/**`. Existuje mnoho různých druhů dokumentačních stylů, zde je představen pouze jeden konkrétní styl. Takový dokumentační komentář můžete využít k vygenerování dokumentace nebo zobrazení informací přímo ve vašem IDE.

Každou proměnnou, funkci, třídu (strukturu) nebo metodu, můžeme (a chceme) tedy jednoduše zdokumentovat přidáním komentáře na začátek této metody, který začíná `/**`. Bývá pravidlem, že první řádek slouží pro krátkou dokumentaci a další řádky pro dlouhou. Každý další řádek bývá uvozen mezerou a hvězdičkou `*` jako je tomu na ukázce.

```cpp
/**
 * Function compares complex numbers.
 * Primary by real part, secondly by imaginary part.
 * @param[in] c1 Complex number
 * @param[in] c2 Complex number
 * @return true if c1 < c2, otherwise false
 */
bool complexCompare ( const Complex & c1, const Complex & c2 )
{
	if ( c1 . getReal() != c2 . getReal() )
		return c1 . getReal() < c2 . getReal();
	return c1 . getImaginary() < c2 . getImaginary();
}
```

Kromě běžného textu je možné uvést informace o předávaných parametrech `@param[dir] nazev_promenne textovy popis`. Parametr `dir` může nabývat hodnot `in` pro vstupní parametry (př.: čísla, která se mají porovnávat), `out` pro výstupní parametry (př.: výsledek funkce předávaný referencí) a `in, out` pro vstupně-výstupní parametry (př.: C++ stream). Dále můžeme uvádět informaci o návratové hodnotě `@return textovy popis`.
