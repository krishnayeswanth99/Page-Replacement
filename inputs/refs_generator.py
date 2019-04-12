for x in range(10):
    import numpy as np
    n_refs = np.random.randint(30,1000)
    max_page = 30
    table_size = 15
    printref = ''
    for i in range(n_refs):
        printref += str(np.random.randint(0,max_page))+' '

    print(table_size)
    print(n_refs)
    print(printref[:-1])
    print()