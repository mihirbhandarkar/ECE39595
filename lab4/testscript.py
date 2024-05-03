def parse_polynomial(poly_str):
    terms = poly_str.split('\n')
    poly = {}
    for term in terms:
        if term:
            coefficient, power = term.split('x^')
            poly[int(power)] = int(coefficient)
    return poly

def format_solution(poly):
    solution = []
    for power, coefficient in sorted(poly.items(), reverse=True):
        solution.append(f"{{{power}, {coefficient}}}")
    return "std::vector<std::pair<power, coeff>> solution = {" + ', '.join(solution) + "};"

if __name__ == "__main__":
    with open("result.txt", "r") as file:
        polynomials_str = file.read()

    polynomials = polynomials_str.split(';')

    solution = None
    with open("result_comp.txt", "w") as file:
        for idx, poly_str in enumerate(polynomials, start=1):
            poly = parse_polynomial(poly_str)
            solution = format_solution(poly)
            # print(f"Solution for Polynomial {idx}:")
            # print(poly_str)
            file.write(solution)
