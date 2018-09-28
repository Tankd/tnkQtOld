# -*-coding:Latin-1 -*
#!/usr/bin/python3

import os # On importe le module os
import sys
import xlrd as xlrd


if  len( sys.argv) < 2 :
	print("argument manquant")
	sys.exit(0)

if str(sys.argv[1]) == "list":
	myBook = xlrd.open_workbook(sys.argv[2])
	print(myBook.sheet_names())


elif str(sys.argv[1]) == "get":
	myBook = xlrd.open_workbook(sys.argv[2])
	sheet = myBook.sheet_by_name(sys.argv[3])

	for r in range(0,sheet.nrows  ) :
		for c in range(0,sheet.ncols   ) :
			data = str(sheet.cell_value(r, c))
			
			if data[-2:] == ".0":
				data = data.replace(".0", "")

			data = data.replace("\n", "<BR>")
			data = data.replace(";", ",")				
			sys.stdout.write( data)
			if  c != sheet.ncols-1:
				sys.stdout.write( ";")
			else	:
				sys.stdout.write( "\r\n")
			

