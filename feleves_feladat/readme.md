# Féléves beadandó

## Pthread :

### Mátrix inverz számítás Gauss–Jordan eliminációval :
	
	Adott NxN mátrix Gauss-Jordan módszer használatával invezének kiszámítása
	
	Párhozamosítás: algoritmus felbontása elkünötíthető részekre, sorok számolása párhuzamosítássa és osztott memóriával

## Open mp :

### Monte Carlo π számolás
	
	Egység négyeztben random számok generálása és ezen számok vizsgálata hogy bele esnek-e a körbe
	
	Párhuzamosítás: több szálon való szám generálás és minden szál a maga számait vizsgálja majd osztott memóriába az eredmény

## Szabadon választott :

### Canny edge detection módszer kép határok feltérképezésére, python cuda használatával
	
	Kép színének megváltoztatása -> kis részekre osztás -> a megadott régiókban különbségek keresése -> kép összeállítása
	
	Párhuzamosítás: szétbontás után egyszerre több régió számolása
	
## Mindhárom program leírására szolgáló pontok:

	- módzser leírása
	- algoritmus komplexitása
	- párhuzamosításra becsléseket adni
	- párhuzamosítás megoldás
	- megvizsgálni párhuzamosítás sikerességét
	- statisztikák
