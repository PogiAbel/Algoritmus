## Beszuró rendező algoritmus

# Pseudo code:

```
InsertionSort(A)
  for j = 2 to A.length
    key = A[j]
    i = j - 1
    while i > 0 and A[i] > key
      A[i+1] = A[i]
      i = i - 1
    end while
    A[i+1] = key
  end for
endcd .. function
```