# Monte Carlo - féle π közelítés
## Feladat leírás:
A π számítására több módszer is létezik. Ebben a feladatban a Monte Carlo
módszert fogjuk alkalmazni. A módszer lényege, hogy egy egység oldalú négyzetbe beírt kör
területét közelítjük a négyzet területével. Ehhez véletlenszerűen pontokat
generálunk a négyzetbe, és megnézzük, hogy hány pont esik a körbe. A kör
területének közelítéséhez a következő képletet használjuk:
π = 4 * (körbe eső pontok száma) / (összes pont száma)

![monte carlo π közelítés](./picture/monteCarlo.png)

## Algoritmus lépései:
- N pont generálása
- N pont ellenőrzése, hogy a körben vannak-e, felhasználva a Pitagorasz-tételt (a<sup>2</sup> + b<sup>2</sup> = c<sup>2</sup>) a kör sugara 1, így a Pitagorasz-tétel a<sup>2</sup> + b<sup>2</sup> <= 1<sup>2</sup> = c<sup>2</sup> = 1
- π közelítése : π = 4 * (körbe eső pontok száma) / (összes pont száma)

## Algoritmus bonyolultsága:
- N pont generálása O(n)
- N pont ellenőrzése O(n)
- Összesen O(n)

## Algoritmus párhuzamosítása:
- N szálon generálunk n pontot, majd minden szálban ellenőrizzük a pontokat, végül összeadjuk az eredményeket.
- N pont generálása O(n/p)
- N pont ellenőrzése O(n/p)
- Összesen O(n/p + log(p))


## Számítási költség és hatékonyság:
- T<sub>seq</sub>(n) = O(n)
- T<sub>par</sub>(p,n) = O(n/p + log(p))
- Számítási költség: C<sub>p</sub> = T<sub>seq</sub>(n)/T<sub>par</sub>(p,n) = O(p/n + log(p))
- Munka: W<sub>seq</sub>(n) = O(n)
- Gyorsítás: S<sub>par</sub>(p,n) = W<sub>seq</sub>(n)/T<sub>par</sub>(p,n) = O(n/(p + nlog(p)))
- Hatékonyság: E<sub>par</sub>(p,n) = S<sub>par</sub>(p,n)/p = O(n/(p<sup>2</sup> + nlog(p)))

## Statisztikák:
### - A programot 20-120 szálon futtattam 20-as lépésekben, 500000000 pont generálásával.
![eredmény](./picture/result_2d_2.png)
- Jól látszik hogy mennyivel jobb eredményeket kapott a párhuzamosítás, azonban több szálon már nem tudott tovább javulni a program, sőt a 120 szálon futtatott program volt, hogy lassabb lett mint a 100 szálon futtatott program. Ez azért lehet mert a szálak közötti kommunikáció már több időt vesz igénybe mint amennyit a szálak párhuzamosításával nyertünk.
### - A programot 20-120 szálon futtattam 20-as lépésekben, 50000000 pont generálásával.
![eredmény](./picture/result_2d_1.png)

## Algoritmus használata 3 dimenzióban:
- A kör helyett a gömböt vesszük alapul, a gömb sugara 1, így a Pitagorasz-tétel a<sup>2</sup> + b<sup>2</sup> + c<sup>2</sup> <= 1<sup>2</sup> = d<sup>2</sup> = 1
- A gömb területének közelítéséhez a következő képletet használjuk :
π = 6 * (gömbbe eső pontok száma) / (összes pont száma)
- A gömb területe: 4 * π * r<sup>2</sup> = 4 * π * 1<sup>2</sup> = 4 * π
- A gömb területének közelítése: 4 * π = 6 * (gömbbe eső pontok száma) / (összes pont száma)
- π közelítése: π = 6 * (gömbbe eső pontok száma) / (összes pont száma)
