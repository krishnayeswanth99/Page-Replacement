import numpy as np
n_refs = np.random.randint(1,1000)
max_page = np.random.randint(n_refs**0.5,10*(n_refs**0.5))
table_size = np.random.randint(0,max_page+1)
printref = ''
for i in range(n_refs):
    printref += str(np.random.randint(0,max_page))+' '

print(table_size)
print(n_refs)
print(printref[:-1])