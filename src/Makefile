CC		= g++
CFLAGS		= -O2 -Wall
OBJS		= main.o comm.o calc.o sha256_calc.o sha256.o
MAIN_CPP	= main.cpp

CALC_CPP	= calc_nonce.cpp
CALC_HPP	= calc_nonce.hpp

SHA256_C	= sha256.c
SHA256_H	= sha256.h
SHA256_CALC_C	= sha256_calc.c
SHA256_CALC_H	= sha256_calc.h

COMM_CPP	= comm.cpp
COMM_HPP	= comm.hpp

BINARY		= calc_pc.bin

bin:		$(OBJS)
		$(CC) $(CFLAGS) -o $(BINARY) $(OBJS)

main.o:		$(MAIN_CPP) comm.o calc.o
		$(CC) $(CFLAGS) -o main.o -c $(MAIN_CPP)

sha256.o:	$(SHA256_C) $(SHA256_H)
		$(CC) $(CFLAGS) -o sha256.o -c $(SHA256_C)

sha256_calc.o:	$(SHA256_CALC_C) $(SHA256_CALC_H) sha256.o
		$(CC) $(CFLAGS) -o sha256_calc.o -c $(SHA256_CALC_C)

calc.o:		$(CALC_CPP) $(CALC_HPP)
		$(CC) $(CFLAGS) -o calc.o -c $(CALC_CPP)

comm.o:		$(COMM_CPP) $(COMM_HPP)
		$(CC) $(CFLAGS) -o comm.o -c $(COMM_CPP)

clean:
		rm main.o calc.o comm.o sha256.o sha256_calc.o $(BINARY)
