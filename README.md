# Detekcija barijera u 2D prostoru pomoću grafova

Ovaj algoritam rešava problem prohodnosti između tačaka $(0,0)$ i $(xCorner, yCorner)$ unutar pravougaonog koordinatnog sistema. Umesto klasične pretrage putanje, algoritam se fokusira na identifikaciju **neprekidnog niza prepreka** koji bi tu putanju onemogućio.

## 🚀 Opis algoritma

Glavni cilj je utvrditi da li krugovi formiraju neprobojnu barijeru između starta i cilja. Suština problema je u sledećem: najbrži i idealni put između $(0,0)$ i $(xCorner, yCorner)$ je **dijagonala**. Krugovi mogu da ometaju tu putanju i potiskuju je, ali putanja će postojati sve dok prepreke ne formiraju lanac koji spaja stranice sa jedne strane dijagonale sa stranicama sa druge strane. 

Ako se krugovi povežu tako da zatvore prostor od jedne ivice do druge, oni efektivno "presecaju" dijagonalu i blokiraju prolaz.






### 🏗️ Modelovanje kroz teoriju grafova
Da bismo efikasno pratili ove lance, krugove strukturiramo kao **graf**:
- **Čvorovi**: Svaki krug predstavlja jedan čvor u grafu.
- **Veze (Grane)**: Veza između dva čvora se uspostavlja ako se krugovi seku ili dodiruju, pod uslovom da je njihov presek relevantan za prostor unutar pravougaonika.
- **Logika prolaza**: Kretanjem kroz graf proveravamo da li možemo da povežemo ivice koje razdvajaju start od cilja.

---

## 🛠️ Faze algoritma

### 1. Inicijalizacija i obrada prepreka
U ovom delu (složenost $O(N^2)$) vršimo pripremu:
- **Validacija pozicije**: Provera da li su sam start ili cilj već "pokriveni" nekim krugom.
- **Izgradnja grafa**: Definišu se sve veze među krugovima. Fokus je na presecima koji se dešavaju unutar pravougaonika ili dovoljno blizu da bi uticali na kretanje.
- **BFS Seed (Početni krugovi)**: Biramo krugove koji dodiruju "početnu" liniju barijere (donju ili desnu ivicu pravougaonika).



### 2. BFS pretraga lanca
BFS pretraga ima zadatak da ispita da li započeti lanac krugova stiže do "završne" linije:
- Pretraga traži bilo koji krug koji seče **levu** ili **gornju** ivicu pravougaonika.
- **Rezultat**: Ako pretraga uspe da spoji ove suprotne strane, putanja je fizički prekinuta i algoritam vraća `false`.

---

## 🔍 Analiza specifičnih slučajeva (Edge Cases)

Algoritam precizno obrađuje situacije koje često zbunjuju standardne provere:
- **Preseci van dometa**: Često se dva kruga seku matematički, ali je taj presek van našeg kvadrata. Algoritam prepoznaje da u tom slučaju između njih ostaje slobodan prostor unutar dometa.
- **Krugovi u uglovima**: Posebna pažnja je posvećena krugovima koji pokrivaju same uglove pravougaonika, čime se direktno prekida svaka mogućnost kretanja.

---

## 📊 Složenost
- **Vremenska složenost**: $O(N^2)$ za izgradnju matrice susedstva/liste.
- **Prostorna složenost**: $O(N^2)$ za čuvanje veza u grafu.
