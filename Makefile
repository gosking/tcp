tpcserv01 : tcpserv01.o str_echo.o readlinel.o writen.o
	gcc -o tcpserv01 tcpserv01.o str_echo.o readlinel.o writen.o
tcpserv01.o : tcpserv01.c
	gcc -c tcpserv01.c
str_echo.o : str_echo.c
	gcc -c str_echo.c
readlinel.o : readlinel.c
	gcc -c readlinel.c
writen.o : writen.c
	gcc -c writen.c

