Name    : Alfredo Mejia
NETID   : axm180023
Course  : SE 3345.004
Assign  : Project 5 // Quick Sort
IDE     : IntelliJ IDEA Community Edition 2019.2.4
Terminal: Git Bash

Summary:
Throughout many different arrays each one produced different outcomes; however, there were some patterns. Ideally the fastest ones were the first element and the random element compared to the other two. However with small input, the median of three elements rarely performed the fastest between all of them. The reason why the other two are lagging behind is because the generation of random indices causes it to take more time. Now between the first element and the random element the report shows the random element has faster times than the first element. The random element and the first element shouldn't be too far apart because ideally if the numbers were truly random it wouldn't matter which element you choose, the performance will stay the same. However, in this case, the random element has more sucess but ideally it shouldn't be like that because like stated previously the first element and the random element should produce identical results: ideally. However not everything is perfectly random, so choosing the first element actually is a bit worse than choosing a random element. This is because the first element tends not to be a number near the middle of the array causing the array to have uneven sublists. On the contrary, choosing a random element gives a better chance of choosing an element that can split the array in an even amount of two sublists. Thus choosing a random element will be better than the first element because not everything is perfectly random and thus shows the best results come from choosing a random element than the first element


Different Reports:

Array Size = 5
FIRST_ELEMENT : PT0.0003843S
RANDOM_ELEMENT : PT0.0000306S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0002088S
MEDIAN_OF_THREE_ELEMENTS : PT0.0000131S

Array Size = 10
FIRST_ELEMENT : PT0.0003238S
RANDOM_ELEMENT : PT0.0000238S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0002336S
MEDIAN_OF_THREE_ELEMENTS : PT0.0000306S

Array Size = 50
FIRST_ELEMENT : PT0.0004393S
RANDOM_ELEMENT : PT0.0001842S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0004034S
MEDIAN_OF_THREE_ELEMENTS : PT0.0001153S

Array Size = 100
FIRST_ELEMENT : PT0.0005757S
RANDOM_ELEMENT : PT0.0005093S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0046041S
MEDIAN_OF_THREE_ELEMENTS : PT0.000282S

Array Size = 500
FIRST_ELEMENT : PT0.0016551S
RANDOM_ELEMENT : PT0.0044799S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0036555S
MEDIAN_OF_THREE_ELEMENTS : PT0.0018522S

Array Size = 1000
FIRST_ELEMENT : PT0.0063556S
RANDOM_ELEMENT : PT0.0011256S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0095992S
MEDIAN_OF_THREE_ELEMENTS : PT0.0023695S

Array Size = 5000
FIRST_ELEMENT : PT0.0113124S
RANDOM_ELEMENT : PT0.0038534S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0152668S
MEDIAN_OF_THREE_ELEMENTS : PT0.0081854S

Array Size = 10000
FIRST_ELEMENT : PT0.0126584S
RANDOM_ELEMENT : PT0.0050587S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT0.0414541S
MEDIAN_OF_THREE_ELEMENTS : PT0.0264326S

Array Size = 50000
FIRST_ELEMENT : PT0.0413351S
RANDOM_ELEMENT : PT0.0393931S
MEDIAN_OF_THREE_RANDOM_ELEMENTS : PT1.1788559S
MEDIAN_OF_THREE_ELEMENTS : PT1.1689427S
