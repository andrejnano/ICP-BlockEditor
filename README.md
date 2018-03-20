# ICP-BlockEditor

> **Aplikacia BlockEditor (projekt do predmetu ICP 2018 @ FIT VUT, BRNO)**

[Oficialne zadanie](https://www.fit.vutbr.cz/study/courses/ICP/public/ICP-PRJ-zadani.html) | 
[Stránka predmetu](https://www.fit.vutbr.cz/study/courses/ICP/public/)

## Základní zadání

Navrhněte a implementujte aplikaci pro návrh a editaci blokových schémat.

### Specifikace požadavků

1. Základní požadavky
    * aplikace umožní vytvářet, editovat, ukládat a načítat bloková schémata
    * každé schéma má svůj jedinečný název
    * vytvořená schémata lze uložit a opětovně načíst
    * schéma je složeno z bloků a propojů mezi bloky

2. Bloky
    * každý blok má definované vstupní a výstupní porty
    * s každým portem je spojen typ, který je reprezentován množinou dat v podobě dvojic název->hodnota; hodnota bude vždy typu double
    * bloky je možné spojit pouze mezi výstupním a vstupním portem
    * každý blok obsahuje výpočet (vzorce), které transformují hodnoty ze vstupních portů na hodnoty výstupních portů

3. Propojení mezi bloky
    * systém kontroluje kompatibilitu vstupního a výstupního portu propoje (stejný typ dat)
    * typ dat je přiřazen propoji automaticky podle spojených portů

4. Výpočet
    * po sestavení (načtení) schématu je možné provést výpočet
    * systém detekuje cykly v schématu; pokud jsou v schématu cykly, nelze provést výpočet
    * systém požádá o vyplnění dat vstupních portů, která nejsou napojena a poté postupně provádí výpočty jednotlivých bloků podle definovaných vzorců v každém bloku
    * při výpočtu se vždy zvýrazní blok, který je právě přepočítáván
    * výpočet lze krokovat (jeden krok = přepočet jednoho bloku)

5. Další podmínky
    * najetím myši nad propoj se zobrazí aktuální stav dat
    * zvažte způsob jednoduchého rozšiřování systému o nové bloky a data

#### Součást odevzdání

Připravte předem alespoň 5 různých bloků a 3 různé typy (množiny) dat

#### Doporučení

Zamyslete se nad použitím vhodných návrhových vzorů

## Užitočné materiály

### C++ learning

* [ICP prednasky :)](https://www.fit.vutbr.cz/study/courses/ICP/public/Prednasky/ICP.pdf)
* [Learn C++ in Y minutes](https://learnxinyminutes.com/docs/c++/)
* [TheChernoProject](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)
* [C++ crash course](http://www.labri.fr/perso/nrougier/teaching/c++-crash-course/#foreword)
* [Learn C++](http://www.learncpp.com/)

### C++ reference / quick lookup

* [C++ cheatsheet](https://github.com/mortennobel/cpp-cheatsheet)
* [C++ reference](http://en.cppreference.com/w/cpp)
* [C++ DevDocs](http://devdocs.io/cpp/)

### Code style & Design patterns

* [Design patterns for humans](https://github.com/kamranahmedse/design-patterns-for-humans)
* [Design Patterns](https://sourcemaking.com/design_patterns)
* [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
* [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
* ... viac na [stranke predmetu](https://www.fit.vutbr.cz/study/courses/ICP/public/)

### Diagram objektov

![block schema](https://raw.githubusercontent.com/andrejnano/ICP-BlockEditor/master/block_schema.png?token=AJo3v1pCtgZkIUmrwMcnkzVy_bmZaef1ks5aundSwA%3D%3D "ICP Block schema")

### keywords, nápady, návhrové vzory, inšpirácia,... 

**keywords**:
> execution chain, assembly line, pipeline, stream, sequence of tasks, stages, dataflow, source, sink, pipe, lazy evaluation, ...

Tento navrhovy vzor je podobny tomu co robime:

[Chain of responsibility - Design patter](https://en.wikipedia.org/wiki/Chain-of-responsibility_pattern)

Mozne ukladanie schemy blokov:

[Memento](https://github.com/kamranahmedse/design-patterns-for-humans#-memento)

[Memento wiki](https://en.wikipedia.org/wiki/Memento_pattern)

...

[I/O Automaton](https://en.wikipedia.org/wiki/Input/output_automaton)

[Pipeline](https://www.cise.ufl.edu/research/ParallelPatterns/PatternLanguage/AlgorithmStructure/Pipeline.htm)

[Collection Pipeline](https://martinfowler.com/articles/collection-pipeline/)

[Pipes and filters](https://docs.microsoft.com/en-us/azure/architecture/patterns/pipes-and-filters)

[Dataflow](https://en.wikipedia.org/wiki/Dataflow)

[Dataflow programming](https://en.wikipedia.org/wiki/Dataflow_programming) *****

[Dataflow architecture](https://en.wikipedia.org/wiki/Dataflow_architecture)

[Lazy evaluation](https://en.wikipedia.org/wiki/Lazy_evaluation)
