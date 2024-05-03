import os
import subprocess

# Path to your test_files directory
test_dir = 'test_files'
# Command template to run Valgrind on your program
valgrind_command = 'valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./chess'


# Get a list of all test case files that start with 'part2'
test_files = [f for f in os.listdir(test_dir) 
              if os.path.isfile(os.path.join(test_dir, f)) and f.startswith('part')]

# Run Valgrind on each test case
check = "no valgrind"
for test_file in test_files:
    test_file_path = os.path.join(test_dir, test_file)
    print(f'Running Valgrind on {test_file_path}')

    # Run the command and capture the output
    command = f'{valgrind_command} < {test_file_path}'

    result = subprocess.run(command, shell=True, capture_output=True, text=True)
    print(result)

    # Check if Valgrind found errors
    if result.returncode != 0:
        print(f'Valgrind detected an error in {test_file_path}')
        print(result.stderr)
        check = "valgrind found"
    else:
        print(f'No errors detected in {test_file_path}')

    print('-----------------------------------')

print()
print(check)


# import sys

# '''
# terminal command:

# python3 testscript.py test_files/part2_4x4_1.txt


# This code script works be in the lab3 fold or at least as long as you have the right file path

# You need to create the isValidScan and underThreatScan and add them to your chessBoard.cc and hh

# void ChessBoard::isValidScan(int n, int m){
#     for(int i = 0; i < n; i++){
#         for(int j = 0; j < m; j++){
#             for(int k = 0; k < n; k++){
#                 for(int x = 0; x < m; x++){
#                     isValidMove(i,j,k,x);
#                 }
#             }
#         }
#     }
# }

# void ChessBoard::underThreatScan(int n, int m){
#     for(int k = 0; k < n; k++){
#         for(int x = 0; x < m; x++){
#             isPieceUnderThreat(k,x);
#         }
#     }
# }

# '''



# color_dict = {"b":"Black", "w":"White"}
# type_dict = {"b":"Bishop", "p":"Pawn", "r":"Rook", "k":"King"}


# FILEIN = open(sys.argv[1])
# FILEIN.readline()
# temp = FILEIN.readline()

# n = temp[0]
# print("    Student::ChessBoard sBoard(" + n +","+ n + ");")
# print()
# temp = FILEIN.readline()
# while(temp[0] != "~"):
#     color = temp[0]
#     type_chess =  temp[2]
#     row = temp[4]
#     col = temp[6]
#     print("    sBoard.createChessPiece(" + color_dict[color] +","+ type_dict[type_chess]+ "," + row +","+ col + ");")
#     temp = FILEIN.readline()
# temp = FILEIN.readline()
# while(temp):
#     if(temp == "isValidScan\n"):
#         print("    sBoard.isValidScan(" + n +","+ n + ");")
#     elif(temp == "underThreatScan\n"):
#         print("    sBoard.underThreatScan(" + n +","+ n + ");")
#         print()
#     else:
#         fromRow = temp[10]
#         fromCol = temp[12]
#         toRow = temp[14]
#         toCol = temp[16]
#         print("    sBoard.movePiece(" + fromRow +","+ fromCol+ "," + toRow +","+ toCol + ");")

#     temp = FILEIN.readline()

