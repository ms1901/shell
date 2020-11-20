
all:
	gcc cat.c -o cat
	gcc loop.c -o loop
	gcc mkdirt.c -o mkdirt
	gcc rm.c -o rm
	gcc date.c -o date
	gcc ls.c -o ls && ./loop