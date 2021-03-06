#
/*
 *    Copyright (C) 2020
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of terminal-DAB
 *
 *    terminal-DAB is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    terminal-DAB is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with terminal-DAB; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef	__WAV_FILES__
#define	__WAV_FILES__

#include	<sndfile.h>
#include        "ringbuffer.h"
#include        "device-handler.h"
#include	<thread>
#include	<atomic>

typedef void (*device_eof_callback_t)(void * userData);

class	wavFiles: public deviceHandler {
public:
			wavFiles	(std::string,
	                                 RingBuffer<std::complex<float>> *,
	                                 void	*userData);
	       		~wavFiles	(void);
	bool		restartReader	(int32_t);
	void		stopReader	(void);
	
private:
	std::string	fileName;
	bool		repeater;
	double		fileOffset;
	void		*userData;
virtual	void		run		(void);
	int32_t		readBuffer	(std::complex<float> *, int32_t);
	RingBuffer<std::complex<float>>	*_I_Buffer;
	std::thread     workerHandle;
	int32_t		bufferSize;
	SNDFILE		*filePointer;
	std::atomic<bool> running;
	int64_t		currPos;
};

#endif

