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
