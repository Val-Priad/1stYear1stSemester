def my_function(a):
    for i in a:
        print(i)


firstArray = []
secondArray = []
for i in range(10):
    firstArray.append(130 - i)
    secondArray.append(120 + i)
my_function(firstArray)
print("\n")
my_function(secondArray)

thirdArray = []
for i in range(10):
    for x in range(10):
        if firstArray[i] == secondArray[x]:
            thirdArray.append(firstArray[i])

print("\nThird Array:")
my_function(thirdArray)
quantity = 0
for i in thirdArray:
    if i < 127:
        quantity += 1
print("Quantity of elements is:", quantity)
