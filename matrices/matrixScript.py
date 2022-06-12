import random


for size in range(10, 201, 10):
    coefficients = str()
    
    for variant in ["a", "b"]:
        with open(f"matrix_{size}x{size}_{variant}.txt" , 'w') as matrix:
            matrix.write(f"{size}\n{size}\n")
            for r in range(size):
                coefficients = ""
                for c in range(size):
                    coefficients += str(random.randint(0,100)) + " "
                coefficients += "\n"
                matrix.write(coefficients)