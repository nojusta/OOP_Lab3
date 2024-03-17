# v1.0_pradinė
Laboratinio darbo nr. 1 v1.0_pradinė versija

1. Nuskaito duomenis iš naudotojo arba failo ir patikrina ar jie yra teisingi (naudojant išimčių valdymą). 
2. Duoda naudotojui galimybė pasirinkti du galutinio balo skaičiavimo būdus - skaičiuojant vidurkį ar medianą.
3. Leidžia pasirinkti 5 skirtingus būdus įvesti, nuskaityti ar sugeneruoti duomenis.
4. Dinamiškai paskiria atmintį pagal įvesta / nuskaitytą duomenų kiekį.
5. Atidaro testavimo failus ir apskaičiuoja laiką, kurį praleidžia apdorojant duomenis iš failų.
6. Visi pranešimai išvedami lietuvių kalbą.
7. Projektas išskaidytas į kelis failus (.h ir .cpp).
8. Generuoja penkis atsitiktinius studentų sąrašų failus, sudarytus iš: 1 000, 10 000, 100 000, 1 000 000, 10 000 000 įrašų
9. Atlieka tyrimus / testavimus su sugeneruotais failais.
10. Surūšiuoja studentus ir išveda į du naujus failus.
11. Yra 3 skirtingi konteinerio tipo pasirinkimai testavimui - vector, deque, list.

## Konteinerių testavimas

### Testavimo sistemos parametrai:

- Saugykla: 256 GB, Integruota NVMe SSD
- Atmintis: 8 GB RAM
- Procesorius: Apple M1


### Naudojant Vector tipo konteinerius:

| Failo dydis | Skaitymo laikas  | Rūšiavimo laikas | Skirstymo laikas | Veikimo laikas |
|-------------|------------------|------------------|------------------|----------------|
| 1 000       | 0.023s           | 0.004s           | 0.005s           | 0.033s         |
| 10 000      | 0.113s           | 0.018s           | 0.023s           | 0.155s         |
| 100 000     | 0.763s           | 0.188s           | 0.237s           | 1.189s         |
| 1 000 000   | 7.448s           | 2.105s           | 2.673s           | 12.227s        |
| 10 000 000  | 74.810s          | 24.911s          | 31.783s          | 131.505s       |

![Vector_pradine](./Images/Vector_pradine.png)

### Naudojant Deque tipo konteinerius:

| Failo dydis | Skaitymo laikas  | Rūšiavimo laikas | Skirstymo laikas | Veikimo laikas |
|-------------|------------------|------------------|------------------|----------------|
| 1 000       | 0.023s           | 0.004s           | 0.005s           | 0.034s         |
| 10 000      | 0.093s           | 0.019s           | 0.023s           | 0.136s         |
| 100 000     | 0.766s           | 0.193s           | 0.239s           | 1.198s         |
| 1 000 000   | 7.312s           | 2.160s           | 2.638s           | 12.111s        |
| 10 000 000  | 73.857s          | 25.580s          | 30.620s          | 130.058s       |

![Deque_pradine](./Images/Deque_pradine.png)

### Naudojant List tipo konteinerius:

| Failo dydis | Skaitymo laikas  | Rūšiavimo laikas | Skirstymo laikas | Veikimo laikas |
|-------------|------------------|------------------|------------------|----------------|
| 1 000       | 0.023s           | 0.003s           | 0.004s           | 0.031s         |
| 10 000      | 0.112s           | 0.018s           | 0.023s           | 0.154s         |
| 100 000     | 0.761s           | 0.247s           | 0.296s           | 1.305s         |
| 1 000 000   | 7.352s           | 3.322s           | 3.818s           | 14.493s        |
| 10 000 000  | 73.862s          | 42.406s          | 47.849s          | 164.118s       |

![List_pradine](./Images/List_pradine.png)
